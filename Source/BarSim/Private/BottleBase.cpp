// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleBase.h"

#include "DropBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Haptics/HapticFeedbackEffect_Curve.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABottleBase::ABottleBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);

	pourer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pourer"));
	pourer->SetupAttachment(meshComp);

	//stream = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Stream"));
	//stream->SetupAttachment(meshComp);
	//stream->AttachToComponent(meshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Pourer"));
}

// Called when the game starts or when spawned
void ABottleBase::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	
	remains = maxContents;
	SetActorTickEnabled(false);
}

// Called every frame
void ABottleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), GetActorUpVector().X, GetActorUpVector().Y, GetActorUpVector().Z);
	float dot = FVector::DotProduct(GetActorUpVector(), upVector);
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
	float streamWidth = FMath::Clamp(angle * 0.3f - 17.0f, 0, 10);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), angle);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), streamWidth);

	if(remains > 0)
	{
		//기울어진 각도가 90도 이상이라면
		if(angle > 90.0f)
		{
			//물줄기 없을때에만 한 번 스폰 시키기
			if(!bStreamOn)
			{
				//UE_LOG(LogTemp, Warning, TEXT("streamOn"));
				waterStream = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), streamFX, pourer->GetSocketLocation(FName("Pourer")), pourer->GetSocketRotation(FName("Pourer")));
				waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 500);
				waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 0.6);
				//물방울 액터 스폰
				FActorSpawnParameters param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ADropBase* drop = GetWorld()->SpawnActor<class ADropBase>(streamDrop, pourer->GetSocketLocation(FName("Pourer")), pourer->GetSocketRotation(FName("Pourer")), param);
				drop->dropMass = 0.05f * streamWidth * DeltaTime;
				drop->sphereComp->AddForce(drop->sphereComp->GetUpVector() * 9.135);
				remains = remains - drop->dropMass;
				// Haptic Feedback
				if(PC)
				{
					if(isGBR)
						PC->PlayHapticEffect(HF_PourLiquid, EControllerHand::Right);
					if(isGBL)
						PC->PlayHapticEffect(HF_PourLiquid, EControllerHand::Left);

				}
				if(pourSoundBoolean==false&&isGrabbingBottle==true)
				{
					UE_LOG(LogTemp, Warning, TEXT("play sound"))
					//pourSoundAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), pourSound, 1, 1, 0, nullptr, false, true);
					pourSoundAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), pourSound, 1, 1, 0);
					pourSoundBoolean=true;
				}
				bStreamOn = true;
			}
			else
			{
				//이미 물줄기가 스폰된 상태라면 물줄기 두께 변경, 
				if(waterStream)
				{
					//UE_LOG(LogTemp, Warning, TEXT("waterStream On"));
					waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 500);
					waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 0.6);
					waterStream->SetRelativeLocation(pourer->GetSocketLocation(FName("Pourer")));
					waterStream->SetRelativeRotation(pourer->GetSocketRotation(FName("Pourer")));
					//물방울 액터 스폰
					FActorSpawnParameters param;
					param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					ADropBase* drop = GetWorld()->SpawnActor<class ADropBase>(streamDrop, pourer->GetSocketLocation(FName("Pourer")), pourer->GetSocketRotation(FName("Pourer")), param);
					if(drop)
					{
						drop->dropMass = 0.05f * streamWidth * DeltaTime;
						drop->sphereComp->AddForce(drop->sphereComp->GetUpVector() * 9.135);	
						remains = remains - drop->dropMass;
					}
				}
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("streamOff"));
			if(waterStream)
			{
				waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 0);
				if(PC)
				{
					if(isGBR)
						PC->StopHapticEffect(EControllerHand::Right);
					if(isGBL)
						PC->StopHapticEffect(EControllerHand::Left);

				}
				if(pourSoundBoolean==true&&pourSoundAudioComp!=nullptr&&isGrabbingBottle==true)
				{
					UE_LOG(LogTemp, Warning, TEXT("stop sound"))
					pourSoundAudioComp->SetActive(false);
					UGameplayStatics::PlaySound2D(GetWorld(), pourStopSound, 1, 1, 0);
					pourSoundBoolean=false;
				}
				bStreamOn = false;
			}

		}
	}
	else
	{
		if(waterStream)
		{
			waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 0);
			bStreamOn = false;
		}
	}
}

void ABottleBase::SetSimulateAndTickDisable()
{
	GetWorldTimerManager().SetTimer(simHandle, FTimerDelegate::CreateLambda([this]()->void
	{
		this->DisableComponentsSimulatePhysics();
		meshComp->SetSimulatePhysics(false);
		this->SetActorTickEnabled(false);
		
	}), 10.0f, false);
}