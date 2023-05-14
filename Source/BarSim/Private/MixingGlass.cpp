// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingGlass.h"

#include "DropBase.h"
#include "MixedDrop.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Strainer.h"
#include "Components/SphereComponent.h"

AMixingGlass::AMixingGlass(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	sphereComp->SetupAttachment(cupComp);
	sphereComp->SetSphereRadius(5.0f);
	sphereComp->SetRelativeLocation(FVector(0,0,17.0f));
	sphereComp->SetCollisionProfileName(FName("StrainerCheck"));
}

void AMixingGlass::BeginPlay()
{
	Super::BeginPlay();
}

void AMixingGlass::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float dot = FVector::DotProduct(GetActorForwardVector(), upVector);
	float dot2 = FVector::DotProduct(GetActorForwardVector(), FVector(-1,0,0));
	
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
	float angle2 = FMath::RadiansToDegrees(FMath::Acos(dot2));
	
	//float streamWidth = FMath::Clamp(angle * 0.3f - 17.0f, 0, 10);
	float streamWidth = 10.0f;

	if(contents > 0)
	{
		if(bStrainerOn)
		{
			//기울어진 각도가 90도 이상이라면
		if(180 - angle2 > (1.1 - contents / cupSize) * 100 && angle <= 90)
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
				AMixedDrop* mixedDrop = GetWorld()->SpawnActor<class AMixedDrop>(streamDrop, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")));
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
					AMixedDrop* mixedDrop = GetWorld()->SpawnActor<class AMixedDrop>(streamDrop, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")));
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

