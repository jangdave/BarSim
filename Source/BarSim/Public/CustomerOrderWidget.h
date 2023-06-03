// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomerOrderWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UCustomerOrderWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetImage(UTexture2D* setTexture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* image_Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> iconImage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Customer;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Customer;
	
	UPROPERTY()
	TArray<FString> womanScriptA;

	UPROPERTY()
	TArray<FString> womanScriptB;

	UPROPERTY()
	TArray<FString> womanScriptC;

	UPROPERTY()
	TArray<FString> womanScriptD;

	UPROPERTY()
	TArray<FString> manScriptA;

	UPROPERTY()
	TArray<FString> manScriptB;

	UPROPERTY()
	TArray<FString> manScriptC;

	UPROPERTY()
	TArray<FString> manScriptD;
	
	UFUNCTION()
	void SetOrderText();
};
