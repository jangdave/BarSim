// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCheckBox.h"
#include "CupBase.h"
#include "HalfSlicedLime.h"
#include "IceCube.h"
#include "MixingGlass.h"
#include "PlayerCharacter.h"
#include "Shaker.h"
#include "Tablet.h"
#include "TabletWidget.h"
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

	tutorialBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tutorialBox"));
	tutorialBox->SetupAttachment(playerStandComp);
	
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

	tutorialBox->SetVisibility(true);
}

void ATutorialCheckBox::FirstStageStart()
{
	GetWorldTimerManager().SetTimer(timerFirst, this, &ATutorialCheckBox::FirstStage, 0.1, true);
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

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}

			// 술의 양 체크
			if(cup->contents >= 2 && tutorial_UI->checkFirst2->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFirst2Check();

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}

			// 가니쉬 체크
			if(cup->garnishArray[0] == true && tutorial_UI->checkFirst3->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFirst3Check();

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}
		}
	}

	if(tutorial_UI->checkFirst1->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkFirst2->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkFirst3->GetCheckedState() == ECheckBoxState::Checked)
	{
		tutorial_UI->SetCheckCup();
	}
}

void ATutorialCheckBox::SecondStageStart()
{
	if(bCheckPlayerOnce != true)
	{
		bCheckPlayerOnce = true;

		// 위젯 플레이
		tutorial_UI->SetSecond();
	}

	GetWorldTimerManager().SetTimer(timerSecond, this, &ATutorialCheckBox::SecondStage, 0.1, true);
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
		if(hitInfo.GetActor()->GetActorNameOrLabel() == "BP_MixingGlass")
		{
			auto mixing = Cast<AMixingGlass>(hitInfo.GetActor());

			if(mixing != nullptr)
			{
				// 술의 양 체크
				if(mixing->contents >= 3 && tutorial_UI->checkSecond1->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetSecond1Check();

					UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
				}

				// 스터 체크
				if(mixing->bStirred != false && tutorial_UI->checkSecond2->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetSecond2Check();

					UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
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

					UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
				}
			}
		}
	}
	
	if(tutorial_UI->checkSecond1->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkSecond2->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkSecond3->GetCheckedState() == ECheckBoxState::Checked)
	{
		tutorial_UI->SetCheckCup();
	}
}

void ATutorialCheckBox::ThirdStageStart()
{
	if(bCheckPlayerOnce != true)
	{
		bCheckPlayerOnce = true;

		// 위젯 플레이
		tutorial_UI->SetThird();
	}
	
	GetWorldTimerManager().SetTimer(timerThird, this, &ATutorialCheckBox::ThirdStage, 0.1, true);
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
		if(hitInfo.GetActor()->GetActorNameOrLabel() == "BP_ShakerCup")
		{
			auto shaker = Cast<AShaker>(hitInfo.GetActor());

			if(shaker != nullptr)
			{
				// 술의 양 체크
				if(shaker->contents >= 3 && tutorial_UI->checkThird1->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetThird1Check();

					UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
				}

				// 쉐이킹 체크
				if(shaker->bShaked != false && tutorial_UI->checkThird2->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetThird2Check();

					UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
				}
			}
		}
		else
		{
			auto cup = Cast<ACupBase>(hitInfo.GetActor());

			if(cup != nullptr)
			{
				// 술의 양 체크
				if(cup->contents >= 2 && tutorial_UI->checkThird3->GetCheckedState() != ECheckBoxState::Checked)
				{
					tutorial_UI->SetThird3Check();

					UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
				}
			}
		}
	}
	
	if(tutorial_UI->checkThird1->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkThird2->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkThird3->GetCheckedState() == ECheckBoxState::Checked)
	{
		tutorial_UI->SetCheckCup();
	}
}

void ATutorialCheckBox::FourthStageStart()
{
	GetWorldTimerManager().SetTimer(timerFourth, this, &ATutorialCheckBox::FourthStage, 0.1, true);
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
	params.AddObjectTypesToQuery(ECC_WorldDynamic);

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
		
		auto tablet = Cast<ATablet>(hitInfo.GetActor());

		if(tablet != nullptr)
		{
			if(tablet->tablet_UI->bCheckTutorialRecipe != false  && tutorial_UI->checkFourth1->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFourth1Check();

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}

			if(tablet->tablet_UI->bCheckTutorialMail != false  && tutorial_UI->checkFourth2->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFourth2Check();

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}
			
			if(tablet->tablet_UI->bCheckTutorialInternet != false  && tutorial_UI->checkFourth3->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFourth3Check();

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}

			if(tablet->tablet_UI->bCheckTutorialOpen != false  && tutorial_UI->checkFourth4->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFourth4Check();

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}

			if(tablet->tablet_UI->bCheckTutorialClose != false  && tutorial_UI->checkFourth5->GetCheckedState() != ECheckBoxState::Checked)
			{
				tutorial_UI->SetFourth5Check();

				UGameplayStatics::PlaySound2D(GetWorld(), checkSound);
			}
		}
	}

	if(tutorial_UI->checkFourth1->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkFourth2->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkFourth3->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkFourth4->GetCheckedState() == ECheckBoxState::Checked && tutorial_UI->checkFourth5->GetCheckedState() == ECheckBoxState::Checked)
	{
		tutorial_UI->SetCheckTablet();
	}
}

void ATutorialCheckBox::OnCheckOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto cup = Cast<ACupBase>(OtherActor);
	auto tablet = Cast<ATablet>(OtherActor);

	if(cup != nullptr)
	{
		if(cup->iceCount == 3 && cup->contents >= 2 && cup->garnishArray[0] == true)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), nextSound);

			GetWorldTimerManager().ClearTimer(timerFirst);
			
			bCheckPlayerOnce = false;
			
			SecondStageStart();
			
			cup->Destroy();
			cup->iceRef1->Destroy();
			cup->iceRef2->Destroy();
			cup->iceRef3->Destroy();
			cup->halfSlicedLimeRef->Destroy();
		}
		else if(cup->bStirred != false && cup->contents >= 2)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), nextSound);

			GetWorldTimerManager().ClearTimer(timerSecond);
			
			bCheckPlayerOnce = false;
			
			ThirdStageStart();
			
			cup->Destroy();
			if(cup->iceRef1)
			{
				cup->iceRef1->Destroy();
			}
			if(cup->iceRef2)
			{
				cup->iceRef2->Destroy();
			}
			if(cup->iceRef3)
			{
				cup->iceRef3->Destroy();
			}
			if(cup->halfSlicedLimeRef)
			{
				cup->halfSlicedLimeRef->Destroy();
			}
		}
		else if(cup->bShaked != false && cup->contents >= 2)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), nextSound);

			GetWorldTimerManager().ClearTimer(timerThird);
			
			tutorial_UI->SetCheckNext();
			
			FTimerHandle timer;
			GetWorldTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([&]()
			{
				tutorialManager->ClearFirstStage();

				bCheckPlayerOnce = false;

				tutorialBox->SetVisibility(false);
			}), 3.0f, false);
		}
	}

	if(tablet != nullptr)
	{
		if(tablet->tablet_UI->bCheckTutorialRecipe != false && tablet->tablet_UI->bCheckTutorialMail != false && tablet->tablet_UI->bCheckTutorialClose != false && tablet->tablet_UI->bCheckTutorialInternet != false && tablet->tablet_UI->bCheckTutorialOpen != false)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), nextSound);

			GetWorldTimerManager().ClearTimer(timerFourth);
			
			tutorial_UI->SetCheckNext();
			
			FTimerHandle timer;
			GetWorldTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([&]()
			{
				tutorialManager->ClearSecondStage();

				tutorialBox->SetVisibility(false);
			}), 3.0f, false);
		}
	}
}

