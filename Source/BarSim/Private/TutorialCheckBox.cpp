// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCheckBox.h"
#include "CupBase.h"
#include "PlayerCharacter.h"
#include "TutorialManager.h"
#include "Components/BoxComponent.h"
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
}

// Called when the game starts or when spawned
void ATutorialCheckBox::BeginPlay()
{
	Super::BeginPlay();

	tutorialManager = Cast<ATutorialManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATutorialManager::StaticClass()));
}

// Called every frame
void ATutorialCheckBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

		if(player != nullptr)
		{
			tutorialManager->ClearFirstStage();
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

		if(player != nullptr)
		{
			tutorialManager->ClearSecondStage();
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

		if(player != nullptr)
		{
			tutorialManager->ClearFourthStage();
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

