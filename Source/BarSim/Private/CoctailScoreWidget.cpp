// Fill out your copyright notice in the Description page of Project Settings.


#include "CoctailScoreWidget.h"
#include "Components/WidgetSwitcher.h"

void UCoctailScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UCoctailScoreWidget::SetScoreSwitcher(int32 idx)
{
	WidgetSwitcher_scoreBox->SetActiveWidgetIndex(idx);
}
