// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCheckBox.h"
#include "CupBase.h"
#include "MixingGlass.h"
#include "PlayerCharacter.h"
#include "TutorialManager.h"
#include "TutorialWidget.h"
#include "Components/BoxComponent.h"
#include "Components/CheckBox.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATutorialCheckBox::ATutorialCheckBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	checkBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("checkBoxComp"));
	SetRootComponent(checkBoxComp);
	
	playerStandComp = CreateDefaultSubobject<USceneComponent>(TEXT("playerStandComp"));
	playerStandComp->SetupAttachment(checkBoxComp);

	tutorialWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("tutorialWidget"));
	tutorialWidget->SetupAttachment(checkBoxComp);
}

// Called when the game starts or when spawned
void ATutorialCheckBox::BeginPlay()
{
	Super::BeginPlay();

	tutorialManager = Cast<ATutorialManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATutorialManager::StaticClass()));

	tutorial_UI = Cast<UTutorialWidget>(tutorialWidget->GetUserWidgetObject());

	checkBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ATutorialCheckBox::OnCheckOverlap);
}

// Called every frame
void ATutorialCheckBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorialCheckBox::StartWelcome()
{
	tutorial_UI->SetWelcome();
}

void ATutorialCheckBox::FirstStageStart()
{
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &ATutorialCheckBox::FirstStage, 0.1, true);
}

void ATutorialCheckBox::FirstStage()
{
	TArray<FOverlapResult> hitsInfo;
	FVector centerLoc = playerStandComp->GetComponentLocation() + GetActorUpVector() * 140;
	FQuat centerRot = playerStandComp->GetComponentQuat();
	FCollisionObjectQueryParams params;
	FCollisionShape checkShape = FCollisionShape::MakeBox(FVector(140));
	params.AddObjectTypesToQuery(ECC_GameTraceChannel9);
	params.AddObjectTypesToQuery(ECC_Pawn);

	GetWorld()->OverlapMultiByObjectType(hitsInfo, centerLoc, centerRot, params, checkShape);
	for(FOverlapResult hitInfo: hitsInfo)
	{
		auto player = Cast<APlayerCharacter>(hitInfo.GetActor());

		if(player != nullptr && bCheckPlayerOnce != true)
		{
			bCheckPlayerOnce = true;

			// 위젯 플레이
			tutorial_UI->SetFirst();
		}
		
		auto cup = Cast<ACupBase>(hitInfo.GetActor());

		if(cup != nullptr)
		{
			// 얼음 3개 체크
			if(cup->iceCount == 3 && tutorial_UI->checkFirst1->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFirst1Check();
			}
			else if(cup->iceCount != 3 && tutorial_UI->checkFirst1->GetCheckedState() != ECheckBoxState::Unchecked)
			{
				tutorial_UI->SetFirst1UnCheck();
			}

			// 술의 양 체크
			if(cup->contents >= 2 && tutorial_UI->checkFirst2->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFirst2Check();
			}

			// 가니쉬 체크
		}
	}

	if(tutorial_UI->checkFirst1->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkFirst2->GetCheckedState() == ECheckBoxState::Checked)
	{
		tutorial_UI->SetCheckCup();
	}

	// 디버그 라인
	DrawDebugBox(GetWorld(), centerLoc, FVector(140), FColor::Red, false, 0.1);
}

void ATutorialCheckBox::SecondStageStart()
{
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &ATutorialCheckBox::SecondStage, 0.1, true);
}

void ATutorialCheckBox::SecondStage()
{
	TArray<FOverlapResult> hitsInfo;
	FVector centerLoc = playerStandComp->GetComponentLocation() + GetActorUpVector() * 140;
	FQuat centerRot = playerStandComp->GetComponentQuat();
	FCollisionObjectQueryParams params;
	FCollisionShape checkShape = FCollisionShape::MakeBox(FVector(140));
	params.AddObjectTypesToQuery(ECC_GameTraceChannel9);
	params.AddObjectTypesToQuery(ECC_Pawn);

	GetWorld()->OverlapMultiByObjectType(hitsInfo, centerLoc, centerRot, params, checkShape);
	for(FOverlapResult hitInfo: hitsInfo)
	{
		auto player = Cast<APlayerCharacter>(hitInfo.GetActor());
		
		if(player != nullptr && bCheckPlayerOnce != true)
		{
			bCheckPlayerOnce = true;

			// 위젯 플레이
			tutorial_UI->SetSecond();
		}

		if(hitInfo.GetActor()->GetActorNameOrLabel() == "BP_MixingGlass1")
		{
			auto mixing = Cast<AMixingGlass>(hitInfo.GetActor());

			if(mixing != nullptr)
			{
				// 술의 양 체크
				if(mixing->contents >= 2 && tutorial_UI->checkSecond1->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetSecond1Check();
				}

				// 스터 체크
				if(mixing->bStirred != false && tutorial_UI->checkSecond2->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetSecond2Check();
				}
			}
		}
		else
		{
			auto cup = Cast<ACupBase>(hitInfo.GetActor());

			if(cup != nullptr)
			{
				// 술의 양 체크
				if(cup->contents >= 2 && tutorial_UI->checkSecond3->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetSecond3Check();
				}
			}
		}
	}
	
	if(tutorial_UI->checkSecond1->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkSecond2->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkSecond3->GetCheckedState() == ECheckBoxState::Checked)
	{
		tutorial_UI->SetCheckCup();
	}
	
	// 디버그 라인
	DrawDebugBox(GetWorld(), centerLoc, FVector(140), FColor::Red, false, 0.1);
}

void ATutorialCheckBox::ThirdStageStart()
{
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &ATutorialCheckBox::ThirdStage, 0.1, true);
}

void ATutorialCheckBox::ThirdStage()
{
	TArray<FOverlapResult> hitsInfo;
	FVector centerLoc = playerStandComp->GetComponentLocation() + GetActorUpVector() * 140;
	FQuat centerRot = playerStandComp->GetComponentQuat();
	FCollisionObjectQueryParams params;
	FCollisionShape checkShape = FCollisionShape::MakeBox(FVector(140));
	params.AddObjectTypesToQuery(ECC_GameTraceChannel9);
	params.AddObjectTypesToQuery(ECC_Pawn);

	GetWorld()->OverlapMultiByObjectType(hitsInfo, centerLoc, centerRot, params, checkShape);
	for(FOverlapResult hitInfo: hitsInfo)
	{
		auto player = Cast<APlayerCharacter>(hitInfo.GetActor());

		if(player != nullptr)
		{
			tutorialManager->ClearThirdStage();
		}
		
		if(player != nullptr && bCheckPlayerOnce != true)
		{
			bCheckPlayerOnce = true;

			// 위젯 플레이
		}
		
		auto cup = Cast<ACupBase>(hitInfo.GetActor());

		if(cup != nullptr)
		{
			
		}
	}

	// 디버그 라인
	DrawDebugBox(GetWorld(), centerLoc, FVector(140), FColor::Red, false, 0.1);
}

void ATutorialCheckBox::FourthStageStart()
{
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &ATutorialCheckBox::FourthStage, 0.1, true);
}

void ATutorialCheckBox::FourthStage()
{
	TArray<FOverlapResult> hitsInfo;
	FVector centerLoc = playerStandComp->GetComponentLocation() + GetActorUpVector() * 140;
	FQuat centerRot = playerStandComp->GetComponentQuat();
	FCollisionObjectQueryParams params;
	FCollisionShape checkShape = FCollisionShape::MakeBox(FVector(140));
	params.AddObjectTypesToQuery(ECC_GameTraceChannel9);
	params.AddObjectTypesToQuery(ECC_Pawn);

	GetWorld()->OverlapMultiByObjectType(hitsInfo, centerLoc, centerRot, params, checkShape);
	for(FOverlapResult hitInfo: hitsInfo)
	{
		auto player = Cast<APlayerCharacter>(hitInfo.GetActor());

		if(player != nullptr && bCheckPlayerOnce != true)
		{
			bCheckPlayerOnce = true;

			// 위젯 플레이
			tutorial_UI->SetFourth();
		}
		
		auto cup = Cast<ACupBase>(hitInfo.GetActor());

		if(cup != nullptr)
		{
			
		}
	}

	// 디버그 라인
	DrawDebugBox(GetWorld(), centerLoc, FVector(140), FColor::Red, false, 0.1);
}

void ATutorialCheckBox::OnCheckOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto cup = Cast<ACupBase>(OtherActor);

	if(cup != nullptr)
	{
		if(cup->iceCount == 3 && cup->contents >= 2)
		{
			tutorialManager->ClearFirstStage();
		}
		else if(cup->bStirred != false && cup->contents >= 2)
		{
			tutorialManager->ClearSecondStage();
		}
	}
}

