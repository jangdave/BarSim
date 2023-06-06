// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManager.h"

#include "BarGameInstance.h"
#include "EngineUtils.h"
#include "TutorialLight.h"
#include "Kismet/GameplayStatics.h"

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

		if(light != nullptr && light->GetActorNameOrLabel() == "BP_TutorialLight1")
		{
			allLights[0] = light;
		}
		else if(light != nullptr && light->GetActorNameOrLabel() == "BP_TutorialLight2")
		{
			allLights[1] = light;
		}
		else if(light != nullptr && light->GetActorNameOrLabel() == "BP_TutorialLight3")
		{
			allLights[2] = light;
		}
		else if(light != nullptr && light->GetActorNameOrLabel() == "BP_TutorialLight4")
		{
			allLights[3] = light;
		}
		else if(light != nullptr && light->GetActorNameOrLabel() == "BP_TutorialLight5")
		{
			allLights[4] = light;
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

		UGameplayStatics::PlaySound2D(GetWorld(), allCheckBoxes[0]->levelSound);
	}), 1.0f, false);

	auto gi = Cast<UBarGameInstance>(GetGameInstance());

	gi->bCheckGameMode = true;
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

	UGameplayStatics::PlaySound2D(GetWorld(), allCheckBoxes[1]->levelSound);
}

void ATutorialManager::ClearSecondStage()
{
	// 불키고 막힌곳 열기
	allLights[2]->TurnOnLight();
	allWalls[1]->OpenCollision();

	// 3단계 시작하기
	allCheckBoxes[1]->Destroy();
	allCheckBoxes[2]->ThirdStageStart();
	allCheckBoxes[2]->StartWelcome();

	UGameplayStatics::PlaySound2D(GetWorld(), allCheckBoxes[2]->levelSound);
}

void ATutorialManager::ClearThirdStage()
{
	// 불키고 막힌곳 열기
	allLights[3]->TurnOnLight();
	allWalls[2]->OpenCollision();

	// 4단계 시작하기
	allCheckBoxes[2]->Destroy();
	allCheckBoxes[3]->FourthStageStart();
	allCheckBoxes[3]->StartWelcome();

	UGameplayStatics::PlaySound2D(GetWorld(), allCheckBoxes[3]->levelSound);
}

void ATutorialManager::ClearFourthStage()
{
	// 막힌곳 열기
	allWalls[3]->OpenCollision();

	// 마무리
	allCheckBoxes[3]->Destroy();
}

