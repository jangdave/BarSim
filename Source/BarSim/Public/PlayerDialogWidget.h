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
	int32 choiceCount;

	UPROPERTY()
	class UBarGameInstance* gi;
	
	UPROPERTY()
	TArray<FString> playerScript1;
	
	UPROPERTY()
	TArray<FString> playerScript2;

	UPROPERTY()
	TArray<FString> playerScript3;
	
	UPROPERTY()
	TArray<FString> playerChoice1;

	UPROPERTY()
	TArray<FString> playerChoice2;

	UPROPERTY()
	TArray<FString> playerChoice3;

	UPROPERTY()
	TArray<FString> playerStartScript;

	//-----------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Player;
	
	//------------------------------------------------------------------0페이지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Left;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
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
	
	UFUNCTION()
	void SetChoice2();
	
	UFUNCTION()
	void SetChoice3();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartPlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void EndPlayer();

	UFUNCTION()
	void LeftAnswer();

	UFUNCTION()
	void RightAnswer();

	UFUNCTION()
	void StartPlayerText(int32 idx);

	UFUNCTION()
	void SetLanguage();
};
