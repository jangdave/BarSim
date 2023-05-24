// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UPlayerDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TArray<FString> playerScript1;

	UPROPERTY()
	TArray<FString> playerChoice1;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Player;

	//------------------------------------------------------------------0페이지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Choice;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Left;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Right;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Left;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Right;

	//------------------------------------------------------------------1페이지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Player;

	UFUNCTION()
	void SetSwitcher(int32 idx);

	UFUNCTION()
	void SetPlayerText(int32 idx);

	UFUNCTION()
	void SetChoice1();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartPlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void EndPlayer();
};
