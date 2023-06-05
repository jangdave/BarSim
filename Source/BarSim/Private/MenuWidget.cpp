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
	btn_QuitGame->OnClicked.AddDynamic(this, &UMenuWidget::ChoiceQuit);

	// 튜토리얼 선택
	btn_TutorialYes->OnClicked.AddDynamic(this, &UMenuWidget::TutorialMode);
	btn_TutorialNo->OnClicked.AddDynamic(this, &UMenuWidget::StoryMode);

	// 이후 메뉴 버튼 바인드
	btn_ResumeGame->OnClicked.AddDynamic(this, &UMenuWidget::ResumeGame);
	// 체크포인트 바인드
	btn_CheckPoint->OnClicked.AddDynamic(this, &UMenuWidget::ChoiceCheck);
	btn_CheckPointYes->OnClicked.AddDynamic(this, &UMenuWidget::CheckYes);
	btn_CheckPointNo->OnClicked.AddDynamic(this, &UMenuWidget::CheckNo);
	// 메인메뉴 바인드
	btn_ResetGame->OnClicked.AddDynamic(this, &UMenuWidget::ChoiceReset);
	btn_MainYes->OnClicked.AddDynamic(this, &UMenuWidget::ResetYes);
	btn_MainNo->OnClicked.AddDynamic(this, &UMenuWidget::ResetNo);
	// 게임종료 바인드
	btn_QuitGame1->OnClicked.AddDynamic(this, &UMenuWidget::ChoiceQuit);
	btn_QuitYes->OnClicked.AddDynamic(this, &UMenuWidget::QuitGameYes);
	btn_QuitNo->OnClicked.AddDynamic(this, &UMenuWidget::QuitGameNo);
}

void UMenuWidget::GameStart()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(1);
}

void UMenuWidget::ChoiceQuit()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(5);
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
		gi->bCheckMenu = true;
		
		parent->Destroy();
	}
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
		gi->bCheckMenu = true;
		
		parent->Destroy();
	}
}

void UMenuWidget::QuitGameYes()
{
	APlayerController* palyer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), palyer, EQuitPreference::Quit, true);
}

void UMenuWidget::QuitGameNo()
{
	if(gi->bCheckMenu != true)
	{
		WidgetSwitcher_Menu->SetActiveWidgetIndex(0);
	}
	else
	{
		WidgetSwitcher_Menu->SetActiveWidgetIndex(2);
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

void UMenuWidget::ChoiceCheck()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(3);
}

void UMenuWidget::CheckYes()
{
	// 체크포인트로 보내기
	if(gi->checkDayCount == 0 || gi->checkDayCount == 1)
	{
		gi->checkDayCount = 0;

		gi->bCheckGameMode = false;

		gi->bCheckMenu = false;

		gi->TotalMoney = {0, 0, 0, 0};
		
		UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
	}
	else if(gi->checkDayCount == 2)
	{
		gi->checkDayCount = 1;

		gi->TotalMoney = {0, 0, 0, 0};
		
		UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
	}
	else
	{
		gi->checkDayCount = 2;
		
		auto twoday = gi->TotalMoney[1];

		auto threeday = gi->TotalMoney[2];

		auto total = gi->TotalMoney[3];

		auto settotal = total - threeday;
		
		gi->TotalMoney = {0, twoday, 0, settotal};
		
		UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
	}
}

void UMenuWidget::CheckNo()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(2);
}

void UMenuWidget::ChoiceReset()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(4);
}

void UMenuWidget::ResetYes()
{
	gi->checkDayCount = 0;

	gi->bCheckGameMode = false;

	gi->bCheckMenu = false;

	gi->TotalMoney = {0, 0, 0, 0};
	
	UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
}

void UMenuWidget::ResetNo()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(2);
}
