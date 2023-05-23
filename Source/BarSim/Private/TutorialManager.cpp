// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManager.h"
#include "EngineUtils.h"
#include "TutorialLight.h"
#include "TutorialWidget.h"

// Sets default values
ATutorialManager::ATutorialManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATutorialManager::BeginPlay()
{
	Super::BeginPlay();

	GetRights();

	GetWalls();

	GetManagers();
	
	StartTutorial();
}

// Called every frame
void ATutorialManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorialManager::GetRights()
{
	for(TActorIterator<ATutorialLight> lights(GetWorld()); lights; ++lights)
	{
		auto light = *lights;

		if(light != nullptr)
		{
			allLights.Add(light);
		}
	}
}

void ATutorialManager::GetWalls()
{
	for(TActorIterator<ATutorialWall> walls(GetWorld()); walls; ++walls)
	{
		auto wall = *walls;

		if(wall != nullptr)
		{
			allWalls.Add(wall);
		}
	}
}

void ATutorialManager::GetManagers()
{
	for(TActorIterator<ATutorialCheckBox> checkBoxes(GetWorld()); checkBoxes; ++checkBoxes)
	{
		auto checkBox = *checkBoxes;

		if(checkBox != nullptr)
		{
			allCheckBoxes.Add(checkBox);
		}
	}
}

void ATutorialManager::StartTutorial()
{
	// 불키기
	allLights[4]->TurnOnLight();
	allLights[0]->TurnOnLight();
	
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([&]()
	{
		// 1단계 시작하기
		allCheckBoxes[0]->FirstStageStart();
		allCheckBoxes[0]->StartWelcome();
	}), 1.0f, false);
}

void ATutorialManager::ClearFirstStage()
{
	// 불키고 막힌곳 열기
	allLights[1]->TurnOnLight();
	allWalls[0]->OpenCollision();

	// 2단계 시작하기
	allCheckBoxes[0]->Destroy();
	allCheckBoxes[1]->SecondStageStart();
	allCheckBoxes[1]->StartWelcome();
}

void ATutorialManager::ClearSecondStage()
{
	// 불키고 막힌곳 열기
	allLights[2]->TurnOnLight();
	allWalls[1]->OpenCollision();

	allCheckBoxes[1]->Destroy();
	allCheckBoxes[2]->ThirdStageStart();
}

void ATutorialManager::ClearThirdStage()
{
	// 불키고 막힌곳 열기
	allLights[3]->TurnOnLight();
	allWalls[2]->OpenCollision();

	allCheckBoxes[2]->Destroy();
	allCheckBoxes[3]->FourthStageStart();
}

void ATutorialManager::ClearFourthStage()
{
	// 막힌곳 열기
	allWalls[3]->OpenCollision();

	allCheckBoxes[3]->Destroy();
}

