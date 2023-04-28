// Fill out your copyright notice in the Description page of Project Settings.


#include "TabletWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UTabletWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_OpenStore->OnClicked.AddDynamic(this, &UTabletWidget::OpenStore);
	btn_CloseStore->OnClicked.AddDynamic(this, &UTabletWidget::CloseStore);
	btn_Recipe->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackMenu->OnClicked.AddDynamic(this, &UTabletWidget::BackMenuPage);
	btn_OpenGinLime->OnClicked.AddDynamic(this, &UTabletWidget::OpenGinLime);
	btn_BackRecipeMenu->OnClicked.AddDynamic(this, &UTabletWidget::BackRecipePage);
}

void UTabletWidget::OpenStore()
{
	
}

void UTabletWidget::CloseStore()
{
	
}

void UTabletWidget::OpenRecipePage()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(1);
}

void UTabletWidget::BackMenuPage()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(0);
}

void UTabletWidget::OpenGinLime()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(2);
}

void UTabletWidget::BackRecipePage()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(1);
}
