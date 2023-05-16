// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BarGameInstance.generated.h"

DECLARE_DELEGATE(FGoMainDele);

/**
 * 
 */
UCLASS()
class BARSIM_API UBarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	FGoMainDele goToMainMapDele;

	UPROPERTY()
	class AGameStartManager* startManager;
	
	UFUNCTION()
	void CheckDay();

	UFUNCTION()
	void BindFunction();

	UPROPERTY()
	int32 checkDayCount;
	
	UPROPERTY(EditAnywhere)
	bool bCheckGameMode;
};
