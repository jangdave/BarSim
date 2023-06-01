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

	// 날짜
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 checkDayCount; // 0

	// 게임모드 체크 불
	UPROPERTY()
	bool bCheckGameMode; // false
};
