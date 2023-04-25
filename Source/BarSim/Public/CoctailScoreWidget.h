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
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* text_Score;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* text_ProcedureScore;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* text_RatioScore;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UTextBlock* text_AmountScore;
};
