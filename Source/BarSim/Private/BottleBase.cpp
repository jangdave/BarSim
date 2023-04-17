// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleBase.h"

#include "DropBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ABottleBase::ABottleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);

	//stream = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Stream"));
	//stream->SetupAttachment(meshComp);
	//stream->AttachToComponent(meshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Pourer"));
}

// Called when the game starts or when spawned
void ABottleBase::BeginPlay()
{
	Super::BeginPlay();
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

	//기울어진 각도가 45도 이상이라면
	if(angle > 60.0f)
	{
		//물줄기 없을때에만 한 번 스폰 시키기
		if(!bStreamOn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("streamOn"));
			waterStream = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), streamFX, meshComp->GetSocketLocation(FName("Pourer")), meshComp->GetSocketRotation(FName("Pourer")));
			waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 50);
			waterStream->SetNiagaraVariableFloat(FString("streamWidth"), streamWidth);
			//물방울 액터 스폰
			ADropBase* drop = GetWorld()->SpawnActor<class ADropBase>(liquorDrop, meshComp->GetSocketLocation(FName("Pourer")), meshComp->GetSocketRotation(FName("Pourer")));
			drop->dropMass = 0.05f * streamWidth * DeltaTime;
			bStreamOn = true;
		}
		else
		{
			//이미 물줄기가 스폰된 상태라면 물줄기 두께 변경, 
			if(waterStream)
			{
				//UE_LOG(LogTemp, Warning, TEXT("waterStream On"));
				waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 50);
				waterStream->SetNiagaraVariableFloat(FString("streamWidth"), streamWidth);
				waterStream->SetRelativeLocation(meshComp->GetSocketLocation(FName("Pourer")));
				waterStream->SetRelativeRotation(meshComp->GetSocketRotation(FName("Pourer")));
				//물방울 액터 스폰
				ADropBase* drop = GetWorld()->SpawnActor<class ADropBase>(liquorDrop, meshComp->GetSocketLocation(FName("Pourer")), meshComp->GetSocketRotation(FName("Pourer")));
				drop->dropMass = 0.05f * streamWidth * DeltaTime;
			}
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("streamOff"));
		if(waterStream)
		{
			waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 0);
			bStreamOn = false;
		}
	}
}

