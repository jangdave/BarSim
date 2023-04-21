// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerOrderWidget.h"
#include "Components/Image.h"

void UCustomerOrderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
	
	GetImage();
}

void UCustomerOrderWidget::GetImage()
{
	auto question = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/questionmark.questionmark'"));
	
	orderImage.Add(question);
	
	auto jackCoc = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/jackcoc.jackcoc'"));

	orderImage.Add(jackCoc);

	auto jinLime = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/jinlime.jinlime'"));

	orderImage.Add(jinLime);

	auto cubaLibre = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/cubalibre.cubalibre'"));

	orderImage.Add(cubaLibre);
}

void UCustomerOrderWidget::SetImage(UTexture2D* setTexture)
{
	image_Order->SetBrushFromTexture(setTexture);
}
