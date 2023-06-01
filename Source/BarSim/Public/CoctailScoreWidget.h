// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoctailScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UCoctailScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_scoreBox;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Score;

	UFUNCTION()
	void SetScoreSwitcher(int32 idx);
};
