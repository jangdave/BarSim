// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingGlass.h"

#include "BarSpoon.h"
#include "DropBase.h"
#include "MixedDrop.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "StirWidget.h"
#include "Strainer.h"
#include "Components/Overlay.h"
#include "Components/SphereComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

AMixingGlass::AMixingGlass(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	sphereComp->SetupAttachment(cupComp);
	sphereComp->SetSphereRadius(5.0f);
	sphereComp->SetRelativeLocation(FVector(0,0,17.0f));
	sphereComp->SetCollisionProfileName(FName("StrainerCheck"));

	stirChecker1 = CreateDefaultSubobject<USphereComponent>(TEXT("stirChecker1"));
	stirChecker1->SetupAttachment(cupComp);
	stirChecker1->SetSphereRadius(1.0f);
	stirChecker1->SetRelativeLocation(FVector(0, 3.5f, 14.0f));
	stirChecker1->SetCollisionProfileName(FName("StirDetector"));

	stirChecker2 = CreateDefaultSubobject<USphereComponent>(TEXT("stirChecker2"));
	stirChecker2->SetupAttachment(cupComp);
	stirChecker2->SetSphereRadius(1.0f);
	stirChecker2->SetRelativeLocation(FVector(0, -3.5f, 14.0f));
	stirChecker2->SetCollisionProfileName(FName("StirDetector"));

	widgetComp2 = CreateDefaultSubobject<UWidgetComponent>(TEXT("stirWidget"));
	widgetComp2->SetupAttachment(cupComp);
	widgetComp2->SetCollisionProfileName(TEXT("NoCollision"));
}

void AMixingGlass::BeginPlay()
{
	Super::BeginPlay();

	stirChecker1->OnComponentBeginOverlap.AddDynamic(this, &AMixingGlass::Stir);
	stirChecker2->OnComponentBeginOverlap.AddDynamic(this, &AMixingGlass::Stir);
}

void AMixingGlass::CupStop()
{
	if(!bStrainerOn)
	{
		auto cupRotYaw = this->GetActorRotation().Yaw;
		this->SetActorRelativeRotation(FRotator(0, cupRotYaw, 0));
	}
}

void AMixingGlass::Stir(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	spoon = Cast<ABarSpoon>(OtherActor);

	if(spoon)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), stirSound, 1, 1, 0);
		//cupComp->SetSimulatePhysics(false);
		if(contents / cupSize >= 0.1f)
		{
			if(bIsStirStarted)
			{
				bIsStirStarted = false;
				bStirWidgetOn = true;
				stirRate = stirRate + 0.5f;
				widgetTime2 = 0;
				timePassed = 0;
			}
			else
			{
				bIsStirStarted = true;
				bStirWidgetOn = true;
				stirRate = stirRate + 0.5f;
				widgetTime2 = 0;
				timePassed = 0;
			}
		}
	}
}

void AMixingGlass::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(timePassed >= 5.0f)
	{
		stirRate = 0;
		bStirWidgetOn = false;
	}

	//스터 위젯 관련
	if(bStirWidgetOn)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("stir started"));
		widgetComp2->SetVisibility(true);
		stirWidget = Cast<UStirWidget>(widgetComp2->GetUserWidgetObject());

		if(stirWidget)
		{
			widgetTime2 = widgetTime2 + DeltaSeconds;
			stirWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			stirWidget->Overlay->SetVisibility(ESlateVisibility::Visible);
			stirWidget->Contents->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(10 * stirRate) / 10) + " Times"));

			if(!bStirWidgetAnimOn)
			{
				stirWidget->StopAnimation(stirWidget->Disappearing);
				stirWidget->PlayAnimation(stirWidget->Appearing);
			}

			//2초 이상 지났으면 애니메이션 재생
			if(widgetTime2 >= 2.0f)
			{
				if(!bStirWidgetAnimOn)
				{
					stirWidget->PlayAnimation(stirWidget->Disappearing);
					bStirWidgetAnimOn = true;
				}
				else
				{
					if(widgetTime2 >= 3.2f)
					{
						stirWidget->SetVisibility(ESlateVisibility::Hidden);
						bStirWidgetOn = false;
						bStirWidgetAnimOn = false;
						widgetTime2 = 0;
					}
				}
			}
			
		}
	}
	else
	{
		widgetComp2->SetVisibility(false);
	}
	

	float dot = FVector::DotProduct(GetActorForwardVector(), upVector);
	float dot2 = FVector::DotProduct(GetActorForwardVector(), FVector(-1,0,0));
	
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
	float angle2 = FMath::RadiansToDegrees(FMath::Acos(dot2));

	UE_LOG(LogTemp, Warning, TEXT("angle2 is %f"), angle2);
	UE_LOG(LogTemp, Warning, TEXT("angle is %f"), angle);
	
	//float streamWidth = FMath::Clamp(angle * 0.3f - 17.0f, 0, 10);
	float streamWidth = 10.0f;

	if(contents > 0)
	{
		if(bStrainerOn)
		{
			//기울어진 각도가 90도 이상이라면
		if(angle2 > (1.1 - contents / cupSize) * 100 && angle <= 90)
		{
			//물줄기 없을때에만 한 번 스폰 시키기
			//UE_LOG(LogTemp, Warning, TEXT("%f"), streamWidth);
			if(!bStreamOn)
			{
				//UE_LOG(LogTemp, Warning, TEXT("streamOn"));
				waterStream = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), streamFX, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")));
				waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 500);
				waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 0.6);
				waterStream->SetVariableMaterial(FName("streamMaterial"), liquorComp->GetMaterial(0));
				//물방울 액터 스폰
				FActorSpawnParameters param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AMixedDrop* mixedDrop = GetWorld()->SpawnActor<class AMixedDrop>(streamDrop, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")), param);
				mixedDrop->dropMass = 0.05f * streamWidth * DeltaSeconds;
				//UE_LOG(LogTemp, Warning, TEXT("drop mass is %f"), mixedDrop->dropMass);
				
				// 새로 스폰시킬 mixedDrop에 있는 배열에 현재 믹싱 글라스에 담긴 배열 그대로 전달
				mixedDrop->NameArray.Empty();
				mixedDrop->NameArray = NameArray;
				mixedDrop->ContentsArray.Empty();
				mixedDrop->ContentsArray = ContentsArray;

				for(int i = 0; i < mixedDrop->ContentsArray.Num(); i++)
				{
					float mixedPercent = mixedDrop->dropMass / contents;
					mixedDrop->ContentsArray[i] = mixedDrop->ContentsArray[i] * mixedPercent;
					//UE_LOG(LogTemp, Warning, TEXT("%d is %f"), i, mixedDrop->ContentsArray[i]);
				}

				mixedDrop->sphereComp->AddForce(mixedDrop->sphereComp->GetUpVector() * 9.135);

				contents = contents - mixedDrop->dropMass;
				mixedDrop->bStirred = bStirred;
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
					waterStream->SetVariableMaterial(FName("streamMaterial"), liquorComp->GetMaterial(0));
					
					waterStream->SetRelativeLocation(cupComp->GetSocketLocation(FName("Mouth")));
					waterStream->SetRelativeRotation(cupComp->GetSocketRotation(FName("Mouth")));
					//물방울 액터 스폰
					FActorSpawnParameters param;
					param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					AMixedDrop* mixedDrop = GetWorld()->SpawnActor<class AMixedDrop>(streamDrop, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")), param);
					mixedDrop->dropMass = 0.05f * streamWidth * DeltaSeconds;
					//UE_LOG(LogTemp, Warning, TEXT("drop mass is %f"), mixedDrop->dropMass);

					// 새로 스폰시킬 mixedDrop에 있는 배열에 현재 믹싱 글라스에 담긴 배열 그대로 전달
					mixedDrop->NameArray.Empty();
					mixedDrop->NameArray = NameArray;
					mixedDrop->ContentsArray.Empty();
					mixedDrop->ContentsArray = ContentsArray;

					for(int i = 0; i < mixedDrop->ContentsArray.Num(); i++) 
					{
						float mixedPercent = mixedDrop->dropMass / contents;
						mixedDrop->ContentsArray[i] = mixedDrop->ContentsArray[i] * mixedPercent;
						//UE_LOG(LogTemp, Warning, TEXT("%d is %f"), i, mixedDrop->ContentsArray[i]);
					}
					mixedDrop->sphereComp->AddForce(mixedDrop->sphereComp->GetUpVector() * 9.135);
					mixedDrop->bStirred = bStirred;
					contents = contents - mixedDrop->dropMass;
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

