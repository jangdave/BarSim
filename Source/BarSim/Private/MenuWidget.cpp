// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "BarGameInstance.h"
#include "MenuWidgetActor.h"
#include "PlayerCharacter.h"
#include "XRLoadingScreenFunctionLibrary.h"
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
	btn_StoryMode->OnPressed.AddDynamic(this, &UMenuWidget::StoryStart);
	btn_ArcadeMode->OnPressed.AddDynamic(this, &UMenuWidget::ArcadeStart);
	btn_QuitGame->OnPressed.AddDynamic(this, &UMenuWidget::ChoiceQuit);

	// 튜토리얼 선택
	btn_TutorialYes->OnPressed.AddDynamic(this, &UMenuWidget::TutorialMode);
	btn_TutorialNo->OnPressed.AddDynamic(this, &UMenuWidget::NoTutorialMode);

	// 이후 메뉴 버튼 바인드
	btn_ResumeGame->OnPressed.AddDynamic(this, &UMenuWidget::ResumeGame);
	// 체크포인트 바인드
	btn_CheckPoint->OnPressed.AddDynamic(this, &UMenuWidget::ChoiceCheck);
	btn_CheckPointYes->OnPressed.AddDynamic(this, &UMenuWidget::CheckYes);
	btn_CheckPointNo->OnPressed.AddDynamic(this, &UMenuWidget::CheckNo);
	// 메인메뉴 바인드
	btn_ResetGame->OnPressed.AddDynamic(this, &UMenuWidget::ChoiceReset);
	btn_MainYes->OnPressed.AddDynamic(this, &UMenuWidget::ResetYes);
	btn_MainNo->OnPressed.AddDynamic(this, &UMenuWidget::ResetNo);
	// 게임종료 바인드
	btn_QuitGame1->OnPressed.AddDynamic(this, &UMenuWidget::ChoiceQuit);
	btn_QuitYes->OnPressed.AddDynamic(this, &UMenuWidget::QuitGameYes);
	btn_QuitNo->OnPressed.AddDynamic(this, &UMenuWidget::QuitGameNo);
}

void UMenuWidget::StoryStart()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(1);
}

void UMenuWidget::ArcadeStart()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(1);
	
	if(gi != nullptr)
	{
		gi->bCheckArcadeMode = true;
	}
}

void UMenuWidget::ChoiceQuit()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(5);
}

void UMenuWidget::NoTutorialMode()
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

	auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(player != nullptr)
	{
		player->PlayerMenuText();
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

	auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(player != nullptr)
	{
		player->PlayerMenuText();
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
	auto currentMap = UGameplayStatics::GetCurrentLevelName(GetWorld());

	if(gi->bCheckArcadeMode != true)
	{
		// 체크포인트로 보내기
		if(gi->checkDayCount == 0 && currentMap != "")
		{
			if(currentMap == "BarStartMap")
			{
				gi->bCheckGameMode = false;

				gi->bCheckMenu = false;

				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();

				UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
			}
			else if(currentMap == "BarTutorialMap")
			{
				gi->bCheckGameMode = false;

				gi->bCheckMenu = true;

				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();

				UGameplayStatics::OpenLevel(GetWorld(), "BarTutorialMap");
			}
		}
		else if(gi->checkDayCount == 1 && currentMap != "")
		{
			if(currentMap == "BarStartMap")
			{
				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
			}
			else if(currentMap == "BarMainMap")
			{
				gi->TotalMoney = {0, 0, 0, 0};

				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarMainMap");
			}
		}
		else if(gi->checkDayCount == 2 && currentMap != "")
		{
			if(currentMap == "BarStartMap")
			{
				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
			}
			else if(currentMap == "BarMainMap")
			{
				auto oneday = gi->TotalMoney[0];

				auto twoday = gi->TotalMoney[1];
				
				auto total = gi->TotalMoney[3];

				auto settotal = total - twoday;
				
				gi->TotalMoney = {oneday, 0, 0, settotal};
				
				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarMainMap");
			}
		}
		else if(gi->checkDayCount == 3 && currentMap != "")
		{
			if(currentMap == "BarStartMap")
			{
				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
			}
			else if(currentMap == "BarMainMap")
			{
				auto oneday = gi->TotalMoney[0];

				auto twoday = gi->TotalMoney[1];
				
				auto threeday = gi->TotalMoney[2];
				
				auto total = gi->TotalMoney[3];

				auto settotal = total - threeday;
				
				gi->TotalMoney = {oneday, twoday, 0, settotal};

				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarMainMap");
			}
		}
	}
	else
	{
		// 체크포인트로 보내기
		if(gi->checkDayCount == 0 && currentMap != "")
		{
			if(currentMap == "BarStartMap")
			{
				gi->bCheckGameMode = false;

				gi->bCheckArcadeMode = false;
				
				gi->bCheckMenu = false;

				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();

				UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
			}
			else if(currentMap == "BarTutorialMap")
			{
				gi->bCheckGameMode = false;

				gi->bCheckMenu = true;

				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();

				UGameplayStatics::OpenLevel(GetWorld(), "BarTutorialMap");
			}
		}
		else if(gi->checkDayCount == 3 && currentMap != "")
		{
			if(currentMap == "BarStartMap")
			{
				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
			}
			else if(currentMap == "BarMainMap")
			{
				gi->TotalMoney = {0, 0, 0, 0};

				UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
				UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
				UGameplayStatics::OpenLevel(GetWorld(), "BarMainMap");
			}
		}
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

	gi->bCheckArcadeMode = false;
	
	gi->bCheckMenu = false;

	gi->TotalMoney = {0, 0, 0, 0};

	UXRLoadingScreenFunctionLibrary::SetLoadingScreen(LoadingTexture, FVector2D(1, 1), FVector(1, 0, 1.5), true, false);
	UXRLoadingScreenFunctionLibrary::ShowLoadingScreen();
	UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
}

void UMenuWidget::ResetNo()
{
	WidgetSwitcher_Menu->SetActiveWidgetIndex(2);
}
