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

void UTutorialWidget::SetFirst2UnCheck()
{
	checkFirst2->SetCheckedState(ECheckBoxState::Unchecked);
}

void UTutorialWidget::SetFirst3Check()
{
	checkFirst3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFirst3UnCheck()
{
	checkFirst3->SetCheckedState(ECheckBoxState::Unchecked);
}

void UTutorialWidget::SetSecond1Check()
{
	checkSecond1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond1UnCheck()
{
	checkSecond1->SetCheckedState(ECheckBoxState::Unchecked);
}

void UTutorialWidget::SetSecond2Check()
{
	checkSecond2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond2UnCheck()
{
	checkSecond2->SetCheckedState(ECheckBoxState::Unchecked);
}

void UTutorialWidget::SetSecond3Check()
{
	checkSecond3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond3UnCheck()
{
	checkSecond3->SetCheckedState(ECheckBoxState::Unchecked);
}
