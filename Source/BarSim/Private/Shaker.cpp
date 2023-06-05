// Fill out your copyright notice in the Description page of Project Settings.


#include "Shaker.h"

#include "MixedDrop.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayerCharacter.h"
#include "ShakerLid.h"
#include "ShakerStrainer.h"
#include "ShakeWidget.h"
#include "Components/AudioComponent.h"
#include "Components/Overlay.h"
#include "Components/SphereComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

AShaker::AShaker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	sphereComp->SetupAttachment(cupComp);
	sphereComp->SetSphereRadius(4.8f);
	sphereComp->SetRelativeLocation(FVector(0,0, 16.3f));

	widgetComp2 = CreateDefaultSubobject<UWidgetComponent>(TEXT("ShakeWidget"));
	widgetComp2->SetupAttachment(cupComp);
	widgetComp2->SetCollisionProfileName(TEXT("NoCollision"));
}

void AShaker::BeginPlay()
{
	Super::BeginPlay();
	shakeWidget = Cast<UShakeWidget>(widgetComp2->GetUserWidgetObject());
}

void AShaker::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Shake();

	//흔들림 감지
	if(bLidOn)
	{
		newPos = GetActorLocation();
		newVelocity = (newPos - startPos) / DeltaSeconds;
		newAcc = (newVelocity - startVelocity) / DeltaSeconds;

		acc = newAcc.Length();

		UE_LOG(LogTemp, Warning, TEXT("%f"), acc);
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
			//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Shaking"));
			//UE_LOG(LogTemp, Warning, TEXT("%f"), shakingTime);
			timePassed = 0;
			widgetTime2 = 0;
			bShakeWidgetOn = true;
			bShakeWidgetAnimOn = false;
			shakingTime = shakingTime + GetWorld()->GetDeltaSeconds();
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

	
	if(timePassed >= 5.0f)
	{
		shakingTime = 0;
		bShakeWidgetOn = false;
	}
	
	//쉐이크 위젯 관련
	if(bShakeWidgetOn)
	{
		widgetComp2->SetVisibility(true);
		
		//플레이어 바라보게 고정
		if(player)
		{
			FVector playerDir = player->VRReplicatedCamera->GetComponentLocation() - GetActorLocation();
			FRotator playerDirRot = playerDir.Rotation();
			widgetComp2->SetWorldRotation(playerDirRot);
		}

		if(shakeWidget)
		{
			widgetTime2 = widgetTime2 + DeltaSeconds;
			shakeWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			shakeWidget->Overlay->SetVisibility(ESlateVisibility::Visible);
			shakeWidget->Contents->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero((100 * shakingTime) / 100)) + " Sec"));

			if(!bShakeWidgetAnimOn)
			{
				shakeWidget->StopAnimation(shakeWidget->Disappearing);
				shakeWidget->PlayAnimation(shakeWidget->Appearing);
			}

			//2초 이상 지났으면 사라지는 애니메이션 재생
			if(widgetTime2 >= 2.0f)
			{
				if(!bShakeWidgetAnimOn)
				{
					shakeWidget->PlayAnimation(shakeWidget->Disappearing);
					bShakeWidgetAnimOn = true;
				}
				else
				{
					if(widgetTime2 >= 3.2f)
					{
						shakeWidget->SetVisibility(ESlateVisibility::Hidden);
						bShakeWidgetOn = false;
						bShakeWidgetAnimOn = false;
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





	
	float dot = FVector::DotProduct(GetActorUpVector(), upVector);
	float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
	//float streamWidth = FMath::Clamp(angle * 0.3f - 17.0f, 0, 10);
	float streamWidth = 10.0f;
	
	if(contents > 0)
	{
		//기울어진 각도가 90도 이상이라면
		if(angle > (1.1 - insideContents / cupSizeOrigin) * 100)
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
					waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 1.0f);
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
						mixedDrop->mixedDropMass = mixedDrop->mixedDropMass + mixedDrop->ContentsArray[i];
					}

					mixedDrop->sphereComp->AddForce(mixedDrop->sphereComp->GetUpVector() * 9.135);

					contents = contents - mixedDrop->mixedDropMass;
					mixedDrop->bStirred = bStirred;
					mixedDrop->bShaked = bShaked;
					LiquorScale();
					
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
						waterStream->SetNiagaraVariableFloat(FString("streamWidth"), 1.0f);
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
							mixedDrop->mixedDropMass = mixedDrop->mixedDropMass + mixedDrop->ContentsArray[i];
							//UE_LOG(LogTemp, Warning, TEXT("%d is %f"), i, mixedDrop->ContentsArray[i]);
						}
						mixedDrop->sphereComp->AddForce(mixedDrop->sphereComp->GetUpVector() * 9.135);
						mixedDrop->bShaked = bShaked;
						contents = contents - mixedDrop->mixedDropMass;
						LiquorScale();
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

void AShaker::Shake()
{
	
}


