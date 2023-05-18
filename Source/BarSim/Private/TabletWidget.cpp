// Fill out your copyright notice in the Description page of Project Settings.


#include "TabletWidget.h"
#include "SpawnManager.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/GeneratedTypeName.h"

void UTabletWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	spawnmg = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));

	// 테블렛 메뉴
	btn_OpenStore->OnClicked.AddDynamic(this, &UTabletWidget::OpenStore);
	btn_CloseStore->OnClicked.AddDynamic(this, &UTabletWidget::CloseStore);
	btn_Recipe->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_Internet->OnClicked.AddDynamic(this, &UTabletWidget::OpenInternet);
	btn_CloseStore->SetIsEnabled(false);
	
	// 테블릿 레시피 메뉴
	btn_BackMenu->OnClicked.AddDynamic(this, &UTabletWidget::OpenMenuPage);
	btn_OpenGinLime->OnClicked.AddDynamic(this, &UTabletWidget::OpenGinLime);
	btn_OpenGinLimeVideo->OnClicked.AddDynamic(this, &UTabletWidget::OpenGinLimeVideo);
	btn_OpenMartini->OnClicked.AddDynamic(this, &UTabletWidget::OpenMartini);
	btn_OpenMartiniVideo->OnClicked.AddDynamic(this, &UTabletWidget::OpenMartiniVideo);
	btn_OpenDaiquiri->OnClicked.AddDynamic(this, &UTabletWidget::OpenDaiquiri);
	btn_OpenDaiquiriVideo->OnClicked.AddDynamic(this, &UTabletWidget::OpenDaiquiriVideo);
	btn_OpenOldPal->OnClicked.AddDynamic(this, &UTabletWidget::OpenOldPal);
	btn_OpenOldPalVideo->OnClicked.AddDynamic(this, &UTabletWidget::OpenOldPalVideo);
	
	// 테블릿 진라임 레시피 & 영상
	btn_BackRecipeMenu0->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu1->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu2->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu3->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu4->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu5->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu6->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu7->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);

	// 테블릿 키보드 입력
	btn_BackMenu1->OnClicked.AddDynamic(this, &UTabletWidget::OpenMenuPage);
	btn_CapsLock->OnClicked.AddDynamic(this, &UTabletWidget::SetCapsLock);
	btn_Enter->OnClicked.AddDynamic(this, &UTabletWidget::SetEnter);
}

void UTabletWidget::OpenStore()
{
	spawnmg->SpawnCustomer();

	btn_OpenStore->SetIsEnabled(false);
}

void UTabletWidget::CloseStore()
{
	UGameplayStatics::OpenLevel(GetWorld(), "StartMap");
	//spawnmg->SpawnOldPal();
}

void UTabletWidget::OpenInternet()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(7);
}

void UTabletWidget::OpenMenuPage()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(0);
}

void UTabletWidget::OpenRecipePage()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(1);
}

void UTabletWidget::OpenGinLime()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(2);
}

void UTabletWidget::OpenGinLimeVideo()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(3);
}

void UTabletWidget::OpenMartini()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(4);
}

void UTabletWidget::OpenMartiniVideo()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(5);
}

void UTabletWidget::OpenDaiquiri()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(6);
}

void UTabletWidget::OpenDaiquiriVideo()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(7);
}

void UTabletWidget::OpenOldPal()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(8);
}

void UTabletWidget::OpenOldPalVideo()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(9);
}

void UTabletWidget::SetCapsLock()
{
	if(bCheckCaps != true)
	{
		// 캡스락 켜짐
		text_btn_1->SetText(FText::FromString("!"));
		text_btn_2->SetText(FText::FromString("@"));
		text_btn_3->SetText(FText::FromString("#"));
		text_btn_4->SetText(FText::FromString("$"));
		text_btn_5->SetText(FText::FromString("%"));
		text_btn_6->SetText(FText::FromString("^"));
		text_btn_7->SetText(FText::FromString("&"));
		text_btn_8->SetText(FText::FromString("*"));
		text_btn_9->SetText(FText::FromString("("));
		text_btn_0->SetText(FText::FromString(")"));
		text_btn_minus->SetText(FText::FromString("_"));
		text_btn_plus->SetText(FText::FromString("+"));
		text_btn_leftSquare->SetText(FText::FromString("{"));
		text_btn_rightSquare->SetText(FText::FromString("}"));
		text_btn_colon->SetText(FText::FromString(":"));
		text_btn_comma->SetText(FText::FromString("<"));
		text_btn_period->SetText(FText::FromString(">"));
		text_btn_slash->SetText(FText::FromString("?"));
		
		bCheckCaps = true;
	}
	else
	{
		// 캡스락 꺼짐
		text_btn_1->SetText(FText::FromString("1"));
		text_btn_2->SetText(FText::FromString("2"));
		text_btn_3->SetText(FText::FromString("3"));
		text_btn_4->SetText(FText::FromString("4"));
		text_btn_5->SetText(FText::FromString("5"));
		text_btn_6->SetText(FText::FromString("6"));
		text_btn_7->SetText(FText::FromString("7"));
		text_btn_8->SetText(FText::FromString("8"));
		text_btn_9->SetText(FText::FromString("9"));
		text_btn_0->SetText(FText::FromString("0"));
		text_btn_minus->SetText(FText::FromString("-"));
		text_btn_plus->SetText(FText::FromString("="));
		text_btn_leftSquare->SetText(FText::FromString("["));
		text_btn_rightSquare->SetText(FText::FromString("]"));
		text_btn_colon->SetText(FText::FromString(";"));
		text_btn_comma->SetText(FText::FromString(","));
		text_btn_period->SetText(FText::FromString("."));
		text_btn_slash->SetText(FText::FromString("/"));

		bCheckCaps = false;
	}
}
