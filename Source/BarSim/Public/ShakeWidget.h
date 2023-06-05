// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShakeWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UShakeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Binding))
	class UTextBlock* Contents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (Binding))
	class UOverlay* Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* Disappearing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* Appearing;
};
