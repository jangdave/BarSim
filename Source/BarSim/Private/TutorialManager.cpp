// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManager.h"
#include "EngineUtils.h"
#include "TutorialLight.h"

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

void ATutorialManager::StartTutorial()
{
	allLights[0]->TurnOnLight();
}

void ATutorialManager::ClearFirstStage()
{
	allLights[0]->TurnOffLight();
	allLights[1]->TurnOnLight();
	allWalls[0]->OpenCollision();
}

void ATutorialManager::ClearSecondStage()
{
	allLights[1]->TurnOffLight();
	allLights[2]->TurnOnLight();
	allWalls[0]->CloseCollision();
	allWalls[1]->OpenCollision();
}

void ATutorialManager::ClearThirdStage()
{
	allLights[2]->TurnOffLight();
	allLights[3]->TurnOnLight();
	allWalls[1]->CloseCollision();
	allWalls[2]->OpenCollision();
}

void ATutorialManager::ClearFourthStage()
{
	allLights[3]->TurnOffLight();
	allLights[4]->TurnOnLight();
	allWalls[2]->CloseCollision();
	allWalls[3]->OpenCollision();
}

