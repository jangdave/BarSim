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
	auto question = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/image/questionmark.questionmark'"));
	
	orderImage.Add(question);
	
	auto GinLime = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/image/Ginlime.Ginlime'"));

	orderImage.Add(GinLime);

	auto Daiquiri = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/image/Daiquiri.Daiquiri'"));

	orderImage.Add(Daiquiri);

	auto Martini = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/image/Martini.Martini'"));

	orderImage.Add(Martini);

	auto OldPal = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Jang/image/OldPal.OldPal'"));

	orderImage.Add(OldPal);
}

void UCustomerOrderWidget::SetImage(UTexture2D* setTexture)
{
	image_Order->SetBrushFromTexture(setTexture);
}
