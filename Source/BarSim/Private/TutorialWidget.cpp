// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/CheckBox.h"
#include "Components/WidgetSwitcher.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(0);
}

void UTutorialWidget::SetWelcome()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(1);
}

void UTutorialWidget::SetFirst()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(2);
}

void UTutorialWidget::SetSecond()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(3);
}

void UTutorialWidget::SetThird()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(4);
}

void UTutorialWidget::SetFourth()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(5);
}

void UTutorialWidget::SetCheckCup()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(6);
}

void UTutorialWidget::SetCheckTablet()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(7);
}

void UTutorialWidget::SetFirst1Check()
{
	checkFirst1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFirst1UnCheck()
{
	checkFirst1->SetCheckedState(ECheckBoxState::Unchecked);
}

void UTutorialWidget::SetFirst2Check()
{
	checkFirst2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFirst3Check()
{
	checkFirst3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond1Check()
{
	checkSecond1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond2Check()
{
	checkSecond2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond3Check()
{
	checkSecond3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetThird1Check()
{
	checkThird1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetThird2Check()
{
	checkThird2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetThird3Check()
{
	checkThird3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth1Check()
{
	checkFourth1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth2Check()
{
	checkFourth2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth3Check()
{
	checkFourth3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth4Check()
{
	checkFourth4->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth5Check()
{
	checkFourth5->SetCheckedState(ECheckBoxState::Checked);
}
