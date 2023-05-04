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

	TArray<FString> GinLime = {"Gin", "Lime"};

	TArray<FString> Martini = {"Gin", "Vermouth"};

	TArray<FString> OldPal = {"Whisky", "Vermouth", "Campari"};

	TArray<FString> Daiquiri = {"Rum", "Lime"};
	
	float amountOfRum;

	float amountOfGin;

	float amountOfWhisky;

	float amountOfLime;
	
	float amountOfVermouth;
	
	float amountOfCampari;

	int32 orderScore = 40;
	
	int32 procedureScore = 20;

	int32 ratioScore = 30;

	int32 amountScore = 10;

	void CheckGin(TArray<FString> cocName);

	void CheckWhisky(TArray<FString> cocName);

	void CheckRum(TArray<FString> cocName);

	void CheckGinLime();

	void CheckMartini();

	void CheckOldPal();

	void CheckDaiquiri();

	void SomethingElse();
};
