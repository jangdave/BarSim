// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TutorialCheckBox.h"
#include "TutorialLight.h"
#include "TutorialWall.h"
#include "GameFramework/Actor.h"
#include "TutorialManager.generated.h"

UCLASS()
class BARSIM_API ATutorialManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TArray<ATutorialLight*> allLights = {0, 0, 0};

	UPROPERTY()
	TArray<ATutorialWall*> allWalls = {0, 0};

	UPROPERTY()
	TArray<ATutorialCheckBox*> allCheckBoxes = {0, 0};
	
	void GetRights();

	void GetWalls();

	void GetManagers();

	void StartTutorial();

	void ClearFirstStage();

	void ClearSecondStage();
};
