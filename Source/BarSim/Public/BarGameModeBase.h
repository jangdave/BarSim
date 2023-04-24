// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BarGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API ABarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABarGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void GetCup(TArray<FString> cocName, TArray<float> cocliter);

	float amountOfRum;

	float amountOfGin;

	float amountOfWhisky;

	float amountOfLime;
	
	float amountOfVermouth;
	
	float amountOfCampari;

	int32 totalScore = 100;

	void CheckGin();

	void CheckWhisky();

	void CheckRum();

	void CheckGinLime();

	void CheckMartini();

	void CheckOldPal();

	void CheckDaiquiri();

	void SomethingElse();
};
