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

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UImage* image_Order;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> orderImage;
};
