// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerOrderWidget.h"
#include "Components/Image.h"

void UCustomerOrderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UCustomerOrderWidget::SetImage(UTexture2D* setTexture)
{
	image_Order->SetBrushFromTexture(setTexture);
}
