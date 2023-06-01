// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OldPalOrderWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UOldPalOrderWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class UBarGameInstance* gi;
	
	UPROPERTY()
	TArray<FString> oldpalScript1;

	UPROPERTY()
	TArray<FString> oldpalScript3;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_oldpal;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_oldpal1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_oldpal2;

	UFUNCTION()
	void SetOldPalText(int32 idx);

	UFUNCTION()
	void SetOldPalRecipe();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartOldPal();

	UFUNCTION(BlueprintImplementableEvent)
	void EndOldPal();
};
