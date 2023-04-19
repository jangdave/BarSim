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
};
