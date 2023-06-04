// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "BarGameInstance.h"
#include "MenuWidgetActor.h"
#include "PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	menuActor = Cast<AMenuWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMenuWidgetActor::StaticClass()));

	gi = Cast<UBarGameInstance>(GetGameInstance());

	// 0일차 메뉴 버튼 바인드
	btn_StoryMode->OnClicked.AddDynamic(this, &UMenuWidget::GameStart);
	btn_QuitGame->OnClicked.AddDynamic(this, &UMenuWidget::QuitGame);
	btn_TutorialYes->OnClicked.AddDynamic(this, &UMenuWidget::TutorialMode);
	btn_TutorialNo->OnClicked.AddDynamic(this, &UMenuWidget::StoryMode);

	// 이후 메뉴 버튼 바인드
	btn_ResumeGame->OnClicked.AddDynamic(this, &UMenuWidget::ResumeGame);
	btn_ResetGame->OnClicked.AddDynamic(this, &UMenuWidget::ResetGame);
	btn_QuitGame1->OnClicked.AddDynamic(this, &UMenuWidget::QuitGame);
}

void UMenuWidget::GameStart()
{
	if(gi->checkDayCount < 1)
	{
		WidgetSwitcher_Menu->SetActiveWidgetIndex(1);
	}
}

void UMenuWidget::QuitGame()
{
	APlayerController* palyer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), palyer, EQuitPreference::Quit, true);
}

void UMenuWidget::TutorialMode()
{
	if(gi != nullptr)
	{
		gi->bCheckGameMode = false;
	}

	auto parent = Cast<AMenuWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMenuWidgetActor::StaticClass()));

	if(parent != nullptr)
	{
		gi->bCheckSpawnMenu = true;
		
		parent->Destroy();
	}
}

void UMenuWidget::StoryMode()
{
	if(gi != nullptr)
	{
		gi->bCheckGameMode = true;
	}

	auto parent = Cast<AMenuWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMenuWidgetActor::StaticClass()));

	if(parent != nullptr)
	{
		gi->bCheckSpawnMenu = true;
		
		parent->Destroy();
	}
}

void UMenuWidget::ResumeGame()
{
	auto parent = Cast<AMenuWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMenuWidgetActor::StaticClass()));

	auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if(parent != nullptr && player != nullptr)
	{
		player->menuWidgetBool = false;
		
		parent->Destroy();
	}
}

void UMenuWidget::ResetGame()
{
	gi->checkDayCount = 0;

	gi->bCheckGameMode = false;

	gi->bCheckMenu = false;

	gi->TotalMoney = {0, 0, 0, 0};
	
	UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
}
