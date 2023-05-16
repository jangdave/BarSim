// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "BarGameInstance.h"
#include "MenuWidgetActor.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	WidgetSwitcher_Menu->SetActiveWidgetIndex(0);
	
	btn_GameStart->OnClicked.AddDynamic(this, &UMenuWidget::GameStart);
	btn_Option->OnClicked.AddDynamic(this, &UMenuWidget::SetOption);
	btn_QuitGame->OnClicked.AddDynamic(this, &UMenuWidget::QuitGame);
	btn_StoryMode->OnClicked.AddDynamic(this, &UMenuWidget::StoryMode);
	btn_Tutorial->OnClicked.AddDynamic(this, &UMenuWidget::Tutorial);
}

void UMenuWidget::GameStart()
{
	auto gi = Cast<UBarGameInstance>(GetGameInstance());
	
	if(gi->checkDayCount < 1)
	{
		WidgetSwitcher_Menu->SetActiveWidgetIndex(1);
	}
	else
	{
		
	}
}

void UMenuWidget::SetOption()
{
	
}

void UMenuWidget::QuitGame()
{
	APlayerController* palyer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), palyer, EQuitPreference::Quit, true);
}

void UMenuWidget::StoryMode()
{
	auto gi = Cast<UBarGameInstance>(GetGameInstance());

	if(gi != nullptr)
	{
		gi->bCheckGameMode = true;
	}

	auto parent = Cast<AMenuWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMenuWidgetActor::StaticClass()));

	if(parent != nullptr)
	{
		parent->Destroy();
	}
}

void UMenuWidget::Tutorial()
{
	auto gi = Cast<UBarGameInstance>(GetGameInstance());

	if(gi != nullptr)
	{
		gi->bCheckGameMode = false;
	}

	auto parent = Cast<AMenuWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMenuWidgetActor::StaticClass()));

	if(parent != nullptr)
	{
		parent->Destroy();
	}
}