// Fill out your copyright notice in the Description page of Project Settings.


#include "Shaker.h"

#include "MixedDrop.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ShakerLid.h"
#include "ShakerStrainer.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AShaker::AShaker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	sphereComp->SetupAttachment(cupComp);
	sphereComp->SetSphereRadius(4.8f);
	sphereComp->SetRelativeLocation(FVector(0,0, 16.3f));
}

void AShaker::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShaker::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	float dot = FVector::DotProduct(GetActorUpVector(), upVector);
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
	//float streamWidth = FMath::Clamp(angle * 0.3f - 17.0f, 0, 10);
	float streamWidth = 10.0f;

	if(strainer)
	{
		bLidOn = strainer->bLidOn;
	}
	else
	{
		bLidOn = false;
	}
	
	if(contents > 0)
	{
		//기울어진 각도가 90도 이상이라면
		if(angle > (1.1 - contents / cupSize) * 100)
		{
			//물줄기 없을때에만 한 번 스폰 시키기
			//UE_LOG(LogTemp, Warning, TEXT("%f"), streamWidth);
			if(!bStreamOn)
			{
				//UE_LOG(LogTemp, Warning, TEXT("streamOn"));
				if(strainer && bStrainerOn && !bLidOn)
				{
					waterStream = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), streamFX, strainer->streamPoint, GetActorRotation());
					waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 500);
					waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 0.6);
					waterStream->SetVariableMaterial(FName("streamMaterial"), liquorComp->GetMaterial(0));
					//물방울 액터 스폰
					AMixedDrop* mixedDrop = GetWorld()->SpawnActor<class AMixedDrop>(streamDrop, strainer->streamPoint, GetActorRotation());
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
					if(pourSoundBoolean==false&&isGrabbingShaker==true)
					{
						UE_LOG(LogTemp, Warning, TEXT("play sound"))
						pourSoundAudioCompS = UGameplayStatics::SpawnSound2D(GetWorld(), pourSoundS, 1, 1, 0);
						pourSoundBoolean=true;
					}
					bStreamOn = true;
				}
			}
			else
			{
				//이미 물줄기가 스폰된 상태라면 물줄기 두께 변경, 
				if(waterStream)
				{
					if(strainer && bStrainerOn && !bLidOn)
					{
						waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 500);
						waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 0.6);
						waterStream->SetVariableMaterial(FName("streamMaterial"), liquorComp->GetMaterial(0));
						
						waterStream->SetRelativeLocation(strainer->streamPoint);
						waterStream->SetRelativeRotation(GetActorRotation());
						
						//waterStream->SetRelativeLocation(cupComp->GetSocketLocation(FName("Mouth")));
						//waterStream->SetRelativeRotation(cupComp->GetSocketRotation(FName("Mouth")));
						
						//물방울 액터 스폰
						AMixedDrop* mixedDrop = GetWorld()->SpawnActor<class AMixedDrop>(streamDrop, strainer->streamPoint, GetActorRotation());
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
						mixedDrop->bShaked = bShaked;
						contents = contents - mixedDrop->dropMass;
					}
				}
			}
		}
		else
		{
			if(waterStream)
			{
				waterStream->SetNiagaraVariableFloat(FString("spawnRate"), 0);
				if(pourSoundBoolean==true&&pourSoundAudioCompS!=nullptr&&isGrabbingShaker==true)
				{
					UE_LOG(LogTemp, Warning, TEXT("stop sound"));
					pourSoundAudioCompS->SetActive(false);
					UGameplayStatics::PlaySound2D(GetWorld(), pourStopSoundS, 1, 1, 0);
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

	//흔들림 감지
	newPos = GetActorLocation();
	newVelocity = (newPos - startPos) / DeltaSeconds;
	newAcc = (newVelocity - startVelocity) / DeltaSeconds;

	acc = newAcc.Length();
	if(acc > shakeAcc)
	{
		bShaking = true;
	}
	else
	{
		bShaking = false;
	}

	if(bShaking)
	{
		shakingTime = shakingTime + DeltaSeconds;
	}

	if(shakingTime >= 10.0f)
	{
		for(int i = 0; i < ShakeArray.Num(); i++)
		{
			ShakeArray[i] = true;
		}
	}

	startPos = newPos;
	startVelocity = newVelocity;
}

void AShaker::LiquorScale()
{
	float contentsRatio = insideContents / cupSize;
	liquorComp->SetRelativeScale3D(FVector(contentsRatio * 0.3 + 0.7,contentsRatio * 0.3 + 0.7,contentsRatio));
}

void AShaker::CupStop()
{
	if(!bStrainerOn)
	{
		auto cupRotYaw = this->GetActorRotation().Yaw;
		this->SetActorRelativeRotation(FRotator(0, cupRotYaw, 0));
	}
}

