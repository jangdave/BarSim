// Fill out your copyright notice in the Description page of Project Settings.


#include "CupBase.h"

#include "CupWidget.h"
#include "DropBase.h"
#include "IceCube.h"
#include "MixedDrop.h"
#include "PlayerCharacter.h"
#include "SteelSink.h"
#include "Components/BoxComponent.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACupBase::ACupBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cupComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cup"));
	SetRootComponent(cupComp);
	cupComp->SetCollisionProfileName(FName("Check"));

	liquorComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquor"));
	liquorComp->SetupAttachment(cupComp);
	liquorComp->SetRelativeScale3D(FVector(0.01f));
	liquorComp->SetCollisionProfileName(FName("Contents"));
	liquorComp->SetVisibility(false);
	
	measureComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Measure"));
	measureComp->SetupAttachment(cupComp);
	measureComp->SetCollisionProfileName(FName("Cup"));
	measureComp->SetVisibility(false);

	igCheckerComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IGChecker"));
	igCheckerComp->SetupAttachment(cupComp);
	igCheckerComp->SetCollisionProfileName(FName("IGChecker"));
	igCheckerComp->SetVisibility(false);

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	widgetComp->SetupAttachment(cupComp);
	widgetComp->SetCollisionProfileName(FName("NoCollision"));
}

// Called when the game starts or when spawned
void ACupBase::BeginPlay()
{
	Super::BeginPlay();

	cupSize = cupSizeOrigin;
	
	measureComp->OnComponentBeginOverlap.AddDynamic(this, &ACupBase::AddLiquor);
	igCheckerComp->OnComponentBeginOverlap.AddDynamic(this, &ACupBase::AddIce);
	igCheckerComp->OnComponentEndOverlap.AddDynamic(this, &ACupBase::ExtractIce);

	//player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
}

// Called every frame
void ACupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WidgetRotate();

	//전체 부피 중 특정 액체가 차지하는 비율만큼 머테리얼 섞기
	//오더 어레이와 컨텐츠 어레이가 있을때만
	if(NameArray.Num() != 0 && ContentsArray.Num() != 0)
	{
		if(NameArray.Find(FString("Gin")) != INDEX_NONE)
		{
			ginInside = ContentsArray[NameArray.Find(FString("Gin"))];
		}
		
		if(NameArray.Find(FString("Lime")) != INDEX_NONE)
		{
			limeInside = ContentsArray[NameArray.Find(FString("Lime"))];
		}

		if(NameArray.Find(FString("Rum")) != INDEX_NONE)
		{
			rumInside = ContentsArray[NameArray.Find(FString("Rum"))];
		}

		if(NameArray.Find(FString("Sugar")) != INDEX_NONE)
		{
			sugarInside = ContentsArray[NameArray.Find(FString("Sugar"))];
		}

		if(NameArray.Find(FString("Vermouth")) != INDEX_NONE)
		{
			vermouthInside = ContentsArray[NameArray.Find(FString("Vermouth"))];
		}

		if(NameArray.Find(FString("Campari")) != INDEX_NONE)
		{
			campariInside = ContentsArray[NameArray.Find(FString("Campari"))];
		}

		if(NameArray.Find(FString("Whiskey")) != INDEX_NONE)
		{
			whiskeyInside = ContentsArray[NameArray.Find(FString("Whiskey"))];
		}
		
		allInside = ginInside + limeInside + rumInside + sugarInside + vermouthInside + campariInside + whiskeyInside;
		float opacity = FMath::Clamp(limeInside / allInside * 2 + whiskeyInside / allInside * 5 + campariInside / allInside * 8, 0.2, 0.8);

		liquorComp->SetScalarParameterValueOnMaterials(FName("Lime"), limeInside / allInside);
		liquorComp->SetScalarParameterValueOnMaterials(FName("Campari"), campariInside / allInside);
		liquorComp->SetScalarParameterValueOnMaterials(FName("Whiskey"), whiskeyInside / allInside);
		liquorComp->SetScalarParameterValueOnMaterials(FName("Opacity"), opacity);
	}

	//timePassed에 시간 누적
	timePassed += DeltaTime;

	//마지막으로 스터포인트 지나고 5초 지나면 stirRate 초기화
	if(timePassed >= 5.0f)
	{
		stirRate = 0;
	}
	
	//충분히 저어진 상태면
	if(stirRate >= stirNeeded)
	{
		if(!MixArray.IsEmpty())
		{
			for(int i = 0; i < MixArray.Num(); i++)
			{
				MixArray[i] = true;
			}
		}
		else
		{
			MixArray.Add(true);
		}
		bStirredLater = true;
	}
	
	//MixArray에 false값인 원소가 하나라도 있거나 비어 있으면
	if(MixArray.Find(false) != INDEX_NONE || MixArray.Num() == 0)
	{
		//안 섞인거
		bStirred = false;
	}
	//MixArray에 false 값인 원소가 하나도 없고 MixArray가 비어있지 않다면
	else
	{
		//섞인거
		bStirred = true;
	}

	//ShakeArray에 false값인 원소가 하나라도 있거나 비어 있으면
	if(ShakeArray.Find(false) != INDEX_NONE || ShakeArray.Num() == 0)
	{
		bShaked = false;
	}
	else
	{
		bShaked = true;
	}


	//위젯 표현
	if(bWidgetOn)
	{
		widgetComp->SetVisibility(true);
		cupWidget = Cast<UCupWidget>(widgetComp->GetUserWidgetObject());
		
		if(cupWidget)
		{
			widgetTime = widgetTime + DeltaTime;
			cupWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			
			if(!bWidgetAnimOn)
			{
				cupWidget->StopAnimation(cupWidget->Disappearing);
				cupWidget->PlayAnimation(cupWidget->Appearing);
			}


			if(widgetNameArray.Num() == 0)
			{
				// cupWidget->Name1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name2->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Name3->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Name4->SetVisibility(ESlateVisibility::Hidden);
				//
				// cupWidget->Contents1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents2->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Contents3->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Contents4->SetVisibility(ESlateVisibility::Hidden);

				cupWidget->Overlay1->SetVisibility(ESlateVisibility::Hidden);
				cupWidget->Overlay2->SetVisibility(ESlateVisibility::Hidden);
				cupWidget->Overlay3->SetVisibility(ESlateVisibility::Hidden);
				cupWidget->Overlay4->SetVisibility(ESlateVisibility::Hidden);
			}
			else if(widgetNameArray.Num() == 1)
			{
				// cupWidget->Name1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name2->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Name3->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Name4->SetVisibility(ESlateVisibility::Hidden);
				//
				// cupWidget->Contents1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents2->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Contents3->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Contents4->SetVisibility(ESlateVisibility::Hidden);

				cupWidget->Overlay1->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay2->SetVisibility(ESlateVisibility::Hidden);
				cupWidget->Overlay3->SetVisibility(ESlateVisibility::Hidden);
				cupWidget->Overlay4->SetVisibility(ESlateVisibility::Hidden);
				
				cupWidget->Name1->SetText(FText::FromString(widgetNameArray[0]));

				cupWidget->Contents1->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[0]) / 100) + "oz"));
			}
			else if(widgetNameArray.Num() == 2)
			{
				// cupWidget->Name1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name2->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name3->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Name4->SetVisibility(ESlateVisibility::Hidden);
				//
				// cupWidget->Contents1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents2->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents3->SetVisibility(ESlateVisibility::Hidden);
				// cupWidget->Contents4->SetVisibility(ESlateVisibility::Hidden);

				cupWidget->Overlay1->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay2->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay3->SetVisibility(ESlateVisibility::Hidden);
				cupWidget->Overlay4->SetVisibility(ESlateVisibility::Hidden);
				
				cupWidget->Name1->SetText(FText::FromString(widgetNameArray[0]));
				cupWidget->Name2->SetText(FText::FromString(widgetNameArray[1]));
				
				cupWidget->Contents1->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[0]) / 100) + "oz"));
				cupWidget->Contents2->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[1]) / 100) + "oz"));
			}
			else if(widgetNameArray.Num() == 3)
			{
				// cupWidget->Name1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name2->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name3->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name4->SetVisibility(ESlateVisibility::Hidden);
				//
				// cupWidget->Contents1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents2->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents3->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents4->SetVisibility(ESlateVisibility::Hidden);

				cupWidget->Overlay1->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay2->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay3->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay4->SetVisibility(ESlateVisibility::Hidden);
				
				cupWidget->Name1->SetText(FText::FromString(widgetNameArray[0]));
				cupWidget->Name2->SetText(FText::FromString(widgetNameArray[1]));
				cupWidget->Name3->SetText(FText::FromString(widgetNameArray[2]));
				
				cupWidget->Contents1->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[0]) / 100) + "oz"));
				cupWidget->Contents2->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[1]) / 100) + "oz"));
				cupWidget->Contents3->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[2]) / 100) + "oz"));
			}
			else if(widgetNameArray.Num() >= 4)
			{
				// cupWidget->Name1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name2->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name3->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Name4->SetVisibility(ESlateVisibility::Visible);
				//
				// cupWidget->Contents1->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents2->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents3->SetVisibility(ESlateVisibility::Visible);
				// cupWidget->Contents4->SetVisibility(ESlateVisibility::Visible);
				
				cupWidget->Overlay1->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay2->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay3->SetVisibility(ESlateVisibility::Visible);
				cupWidget->Overlay4->SetVisibility(ESlateVisibility::Visible);
				
				cupWidget->Name1->SetText(FText::FromString(widgetNameArray[0]));
				cupWidget->Name2->SetText(FText::FromString(widgetNameArray[1]));
				cupWidget->Name3->SetText(FText::FromString(widgetNameArray[2]));
				cupWidget->Name4->SetText(FText::FromString(widgetNameArray[3]));
				
				cupWidget->Contents1->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[0]) / 100) + "oz"));
				cupWidget->Contents2->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[1]) / 100) + "oz"));
				cupWidget->Contents3->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[2]) / 100) + "oz"));
				cupWidget->Contents4->SetText(FText::FromString(FString::SanitizeFloat(FMath::RoundHalfToZero(100 * widgetContentsArray[3]) / 100) + "oz"));
			}

			//2초 이상 지났으면 애니메이션 재생
			if(widgetTime >= 2.0f)
			{
				if(!bWidgetAnimOn)
				{
					cupWidget->PlayAnimation(cupWidget->Disappearing);
					bWidgetAnimOn = true;
				}
				else
				{
					if(widgetTime >= 3.2f)
					{
						cupWidget->SetVisibility(ESlateVisibility::Hidden);
						bWidgetOn = false;
						bWidgetAnimOn = false;
						widgetTime = 0;
						widgetNameArray.Empty();
						widgetContentsArray.Empty();
					}
				}
			}
			
		}
	}
	else
	{
		widgetComp->SetVisibility(false);
	}
	
	if(isCupTickActivated)
	{
		CupStop();
	}
}

void ACupBase::AddLiquor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	mixedDropOverlapped = Cast<AMixedDrop>(OtherActor);
	// 섞인 방울이 컵에 담기면
	if(mixedDropOverlapped)
	{
		overlappedNum ++;
		//방울에 NameArray가 있다면
		if(!mixedDropOverlapped->NameArray.IsEmpty())
		{
			for(int i = 0; i < mixedDropOverlapped->NameArray.Num(); i++)
			{
				//컵의 NameArray에 같은 이름을 가진 원소가 있다면
				if(NameArray.Find(mixedDropOverlapped->NameArray[i]) != INDEX_NONE)
				{
					//해당 원소의 순서의 ContentsArray이 가진 기존 배열값에 새 방울이 가진 ContentsArray 값을 더해줌
					ContentsArray[NameArray.Find(mixedDropOverlapped->NameArray[i])] = ContentsArray[NameArray.Find(mixedDropOverlapped->NameArray[i])] + mixedDropOverlapped->ContentsArray[i];
				}
				//컵의 NameArray에 같은 이름이 없다면
				else
				{
					//새로 추가
					NameArray.Emplace(mixedDropOverlapped->NameArray[i]);
					ContentsArray.Add(mixedDropOverlapped->ContentsArray[i]);
				}
			}

			// 이미 위젯 네임어레이에 믹스쳐라는 원소가 있다면 그대로 해당 순서의 위젯 컨텐츠 어레이에 더해줌
			if(widgetNameArray.Find(FString("Mixture")) != INDEX_NONE)
			{
				float mixtureMass = 0;
				for(int i = 0; i < mixedDropOverlapped->NameArray.Num(); i++)
				{
					mixtureMass = mixtureMass + mixedDropOverlapped->ContentsArray[i];
				}
				widgetContentsArray[widgetNameArray.Find(FString("Mixture"))] = widgetContentsArray[widgetNameArray.Find(FString("Mixture"))] + mixtureMass; 
			}
			// 위젯 네임 어레이에 믹스쳐라는 원소가 없다면 새로 믹스쳐라는 이름의 원소를 위젯 네임어레이에 추가하고 믹스드드랍의 부피를 더해줌
			else
			{
				widgetNameArray.Emplace(FString("Mixture"));
				float mixtureMass = 0;
				for(int i = 0; i < mixedDropOverlapped->NameArray.Num(); i++)
				{
					mixtureMass = mixtureMass + mixedDropOverlapped->ContentsArray[i];
				}
				widgetContentsArray.Add(mixtureMass);
			}

			//위젯 나타내기
			bWidgetOn = true;
			widgetTime = 0;
			bWidgetAnimOn = false;
			
			MixArray.Add(mixedDropOverlapped->bStirred);
			ShakeArray.Add(mixedDropOverlapped->bShaked);
			contents = contents + mixedDropOverlapped->dropMass;
			insideContents = FMath::Clamp(contents, 0, cupSize);
			liquorComp->SetVisibility(true);
			LiquorScale();
			mixedDropOverlapped->DropDestroyDelay();
		}
	}
	else
	{
		drop = Cast<ADropBase>(OtherActor);
		if(drop)
		{
			overlappedNum ++;
			//들어온 방울 액터가 가진 이름을 NameArrary에, 유량을 ContentsArray에 저장한다.
			if(!NameArray.IsEmpty())
			{
				//NameArray에 이미 저장된 이름이라면
				if(NameArray.Find(drop->name) != INDEX_NONE)
				{
					//해당 배열 순서의 ContentsArray에 기존값에 새로 오버랩된 방울 액터의 dropMass 값을 더해서 넣어주고
					ContentsArray[NameArray.Find(drop->name)] = ContentsArray[NameArray.Find(drop->name)] + drop->dropMass;
				}
				//NameArray에 저장되어 있지 않은 이름이라면 
				else
				{
					//새로운 NameArray와 ContentsArray에 넣는다.
					NameArray.Emplace(drop->name);
					ContentsArray.Add(drop->dropMass);
				}
			}
			else
				//배열이 비어있을 경우 값 하나 일단 넣기
				{
				NameArray.Emplace(drop->name);
				ContentsArray.Add(drop->dropMass);
				}

			// 실시간으로 담기는 용량 위젯 표시용
			// 이미 위젯 네임어레이가 비어있지 않다면
			if(!widgetNameArray.IsEmpty())
			{
				// 위젯 네임 어레이에 새로 들어온 방울의 이름이 있다면 그대로 값에 더해줌
				if(widgetNameArray.Find(drop->name) != INDEX_NONE)
				{
					widgetContentsArray[widgetNameArray.Find(drop->name)] = widgetContentsArray[widgetNameArray.Find(drop->name)] + drop->dropMass; 
				}
				// 위젯 네임 어레이에 새로 들어온 방울의 이름이 없다면 새로 추가해 줌
				else
				{
					widgetNameArray.Emplace(drop->name);
					widgetContentsArray.Add(drop->dropMass);
				}
			}
			// 위젯 네임 어레이가 없다면 위젯 네임 어레이와 위젯 컨텐츠 어레이에 하나씩 새로 넣어줌
			else
			{
				widgetNameArray.Emplace(drop->name);
				widgetContentsArray.Add(drop->dropMass);
			}

			//위젯 나타내기
			bWidgetOn = true;
			widgetTime = 0;
			bWidgetAnimOn = false;
			
			contents = contents + drop->dropMass;
			insideContents = FMath::Clamp(contents, 0, cupSize);
			liquorComp->SetVisibility(true);
			LiquorScale();
			MixArray.Add(false);
			ShakeArray.Add(false);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("drop overlapped"));
			drop->DropDestroyDelay();
		}
	}
	
}

void ACupBase::AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ice = Cast<AIceCube>(OtherActor);
	//igchecker에 얼음이 오버랩되었을 때
	if(ice)
	{
		iceCount += 1;
		//얼음 갯수 하나당 2온스씩 내부 용량 줄이기
		cupSize = cupSizeOrigin - iceCount * 2;
		insideContents = FMath::Clamp(contents, 0, cupSize);
		LiquorScale();
	}
}

void ACupBase::ExtractIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ice = Cast<AIceCube>(OtherActor);
	//igchecker에 얼음이 오버랩해제되었을 때
	if(ice)
	{
		iceCount -= 1;
		//얼음 갯수 하나당 2온스씩 내부 용량 줄이기
		cupSize = cupSizeOrigin - iceCount * 2;
		insideContents = FMath::Clamp(contents, 0, cupSize);
		LiquorScale();

	}
}

void ACupBase::LiquorScale()
{
	liquorComp->SetRelativeScale3D(FVector(1,1,insideContents / cupSize));
}

void ACupBase::SetCupEmpty()
{
	FVector Center = cupComp->GetComponentLocation();
	TArray<FOverlapResult> HitObj;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	//DrawDebugSphere(GetWorld(), Center, 10, 30, FColor::Red, false, 2.0, 0, 0.1);
	bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(10), params);
	if (bHit == false)
	{
		return;
	}
	for(int i=0; i<HitObj.Num(); ++i)
	{
		steelSink = Cast<ASteelSink>(HitObj[i].GetActor());
		{
			if(steelSink)
			{
				isSteelSinkCasted = true;
				sinkArrayNum = i;
				UE_LOG(LogTemp, Warning, TEXT("Casting Success"))
			}
		}
	}
	if(isSteelSinkCasted)
	{
		steelSink=Cast<ASteelSink>(HitObj[sinkArrayNum].GetActor());
		if(steelSink!=nullptr)
		{
				UE_LOG(LogTemp, Warning, TEXT("Set Cup Empty"));
				NameArray.Empty();
				ContentsArray.Empty();
				liquorComp->SetVisibility(false);
				bStirred=false;
				contents=0;
				isSteelSinkCasted=false;
		}
	}
}

void ACupBase::CupStop()
{
	auto cupRotYaw = this->GetActorRotation().Yaw;
	this->SetActorRelativeRotation(FRotator(0, cupRotYaw, 0));
}

void ACupBase::WidgetRotate()
{
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if(player)
	{
		//FVector playerDir = player->GetActorLocation() - GetActorLocation();
		FVector playerDir = player->VRReplicatedCamera->GetComponentLocation() - GetActorLocation();
		FRotator playerDirRot = playerDir.Rotation();
		widgetComp->SetWorldRotation(FRotator(playerDirRot));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player casting failed"));
	}
}

