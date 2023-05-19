// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BarGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API ABarGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABarGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	class UBarGameInstance* gi;

	UFUNCTION()
	void SpawnMenu();
};
