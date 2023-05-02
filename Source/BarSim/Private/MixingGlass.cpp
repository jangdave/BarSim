// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingGlass.h"

#include "DropBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"

void AMixingGlass::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float dot = FVector::DotProduct(GetActorUpVector(), upVector);
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
	float streamWidth = FMath::Clamp(angle * 0.3f - 17.0f, 0, 10);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), angle);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), streamWidth);

	if(contents > 0)
	{
		//기울어진 각도가 90도 이상이라면
		if(angle > 60.0f)
		{
			//물줄기 없을때에만 한 번 스폰 시키기
			if(!bStreamOn)
			{
				//UE_LOG(LogTemp, Warning, TEXT("streamOn"));
				waterStream = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), streamFX, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")));
				waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 500);
				waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 0.6);
				//물방울 액터 스폰
				ADropBase* mixedDrop = GetWorld()->SpawnActor<class ADropBase>(streamDrop, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")));
				mixedDrop->dropMass = 0.05f * streamWidth * DeltaSeconds;
				mixedDrop->sphereComp->AddForce(mixedDrop->sphereComp->GetUpVector() * 9.135);
				contents = contents - mixedDrop->dropMass;
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
					waterStream->SetRelativeLocation(cupComp->GetSocketLocation(FName("Mouth")));
					waterStream->SetRelativeRotation(cupComp->GetSocketRotation(FName("Mouth")));
					//물방울 액터 스폰
					ADropBase* mixedDrop = GetWorld()->SpawnActor<class ADropBase>(streamDrop, cupComp->GetSocketLocation(FName("Mouth")), cupComp->GetSocketRotation(FName("Mouth")));
					mixedDrop->dropMass = 0.05f * streamWidth * DeltaSeconds;
					mixedDrop->sphereComp->AddForce(mixedDrop->sphereComp->GetUpVector() * 9.135);
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
	else
	{
		if(waterStream)
		{
			waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 0);
			bStreamOn = false;
		}
	}
}
