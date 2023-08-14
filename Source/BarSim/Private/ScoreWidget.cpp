// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

#include "BarGameInstance.h"
#include "XRLoadingScreenFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/RendererSettings.h"
#include "Kismet/GameplayStatics.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UBarGameInstance>(GetGameInstance());

	if(gi)
	{
		totalMoneyText->SetText(FText::FromString("$ " + FString::SanitizeFloat( FMath::RoundHalfToZero(100 * gi->TotalMoney[0]) / 100)));
	}

	btn_MainMenu->OnClicked.AddDynamic(this, &UScoreWidget::MainMenuCall);
	btn_MainMenuYes->OnClicked.AddDynamic(this, &UScoreWidget::GoMainMenu);
	btn_MainMenuNo->OnClicked.AddDynamic(this, &UScoreWidget::Cancel);

	btn_Quit->OnClicked.AddDynamic(this, &UScoreWidget::QuitCall);
	btn_QuitYes->OnClicked.AddDynamic(this, &UScoreWidget::GoQuit);
	btn_QuitNo->OnClicked.AddDynamic(this, &UScoreWidget::Cancel);
	
}

void UScoreWidget::MainMenuCall()
{
	WidgetSwitcher_Score->SetActiveWidgetIndex(1);
}

void UScoreWidget::QuitCall()
{
	WidgetSwitcher_Score->SetActiveWidgetIndex(2);
}

void UScoreWidget::GoMainMenu()
{
	gi->checkDayCount = 0;

	gi->bCheckTutorialMode = false;

	gi->bCheckMenu = false;

	gi->TotalMoney = {0, 0, 0, 0};

	UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1), true, false);
	UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
	//메인메뉴로 이동
	UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
}

void UScoreWidget::GoQuit()
{
	//게임 종료
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UScoreWidget::Cancel()
{
	WidgetSwitcher_Score->SetActiveWidgetIndex(0);
}
