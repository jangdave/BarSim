// Fill out your copyright notice in the Description page of Project Settings.


#include "TabletWidget.h"
#include "BarGameInstance.h"
#include "PlayerCharacter.h"
#include "SpawnManager.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UTabletWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	spawnmg = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));

	gi = Cast<UBarGameInstance>(GetGameInstance());
	
	// 테블렛 메뉴
	btn_OpenStore->OnPressed.AddDynamic(this, &UTabletWidget::OpenStore);
	btn_CloseStore->OnPressed.AddDynamic(this, &UTabletWidget::CloseStore);
	btn_Recipe->OnPressed.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_Internet->OnPressed.AddDynamic(this, &UTabletWidget::OpenInternet);

	if(gi->checkDayCount != 0)
	{
		btn_CloseStore->SetIsEnabled(false);
	}

	if(gi->checkDayCount == 1)
	{
		btn_OpenStore->SetIsEnabled(false);

		spawnmg->bCheckSpawn = true;
	}
	
	// 테블릿 레시피 메뉴
	btn_BackMenu->OnPressed.AddDynamic(this, &UTabletWidget::OpenMenuPage);
	btn_OpenGinLime->OnPressed.AddDynamic(this, &UTabletWidget::OpenGinLime);
	btn_OpenGinLimeVideo->OnPressed.AddDynamic(this, &UTabletWidget::OpenGinLimeVideo);
	btn_OpenMartini->OnPressed.AddDynamic(this, &UTabletWidget::OpenMartini);
	btn_OpenMartiniVideo->OnPressed.AddDynamic(this, &UTabletWidget::OpenMartiniVideo);
	btn_OpenDaiquiri->OnPressed.AddDynamic(this, &UTabletWidget::OpenDaiquiri);
	btn_OpenDaiquiriVideo->OnPressed.AddDynamic(this, &UTabletWidget::OpenDaiquiriVideo);
	btn_OpenOldPal->OnPressed.AddDynamic(this, &UTabletWidget::OpenOldPal);
	btn_OpenOldPalVideo->OnPressed.AddDynamic(this, &UTabletWidget::OpenOldPalVideo);
	
	// 테블릿 진라임 레시피 & 영상
	btn_BackRecipeMenu0->OnPressed.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu1->OnPressed.AddDynamic(this, &UTabletWidget::OpenGinLime);
	btn_BackRecipeMenu2->OnPressed.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu3->OnPressed.AddDynamic(this, &UTabletWidget::OpenMartini);
	btn_BackRecipeMenu4->OnPressed.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu5->OnPressed.AddDynamic(this, &UTabletWidget::OpenDaiquiri);
	btn_BackRecipeMenu6->OnPressed.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu7->OnPressed.AddDynamic(this, &UTabletWidget::OpenOldPal);

	// 메일함
	btn_Mail->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);

	btn_Inbox->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_Outbox->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);
	btn_InMail1->OnPressed.AddDynamic(this, &UTabletWidget::OpenInMail1);
	btn_InMail2->OnPressed.AddDynamic(this, &UTabletWidget::OpenInMail2);
	btn_InMail3->OnPressed.AddDynamic(this, &UTabletWidget::OpenInMail3);

	btn_BackInMail1->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_1->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_2->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);

	btn_BackInMail1_3->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_4->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_5->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);

	btn_BackInMail1_6->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_7->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_8->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);

	btn_Inbox_1->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_Outbox_1->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);
	btn_InMail1_1->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutMail1);
	btn_InMail2_1->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutMail2);

	btn_BackInMail1_9->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);
	btn_BackInMail1_10->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_11->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);

	btn_BackInMail1_12->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);
	btn_BackInMail1_13->OnPressed.AddDynamic(this, &UTabletWidget::OpenInbox);
	btn_BackInMail1_14->OnPressed.AddDynamic(this, &UTabletWidget::OpenOutbox);
	
	// 테블릿 키보드 입력
	btn_CapsLock->OnPressed.AddDynamic(this, &UTabletWidget::SetCapsLock);
	btn_Enter->OnPressed.AddDynamic(this, &UTabletWidget::SetEnter);

	// 커서 Visibility 설정
	CursorRight->SetVisibility(ESlateVisibility::Hidden);
	CursorLeft->SetVisibility(ESlateVisibility::Hidden);

	// Player Casting
	FTimerHandle castHandle;
	GetWorld()->GetTimerManager().SetTimer(castHandle, this, &UTabletWidget::CastToPlayerCharacter, 2.0f, false);

	// 초기값 설정
	totalMoney->SetText(FText::AsNumber(0.0));
	todayMoney->SetText(FText::AsNumber(0.0));
}

void UTabletWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Player가 Nullptr가 아닐 때
	if(player!=nullptr)
	{
		// 플레이어의 Widget Interaction Component가 위젯과 닿아있다면
		bool bIsCursorOn = player->widgetInteractionComp->IsOverHitTestVisibleWidget();
		if(bIsCursorOn)
		{
			// 커서를 보이게 하고, 닿은 2D 위치값으로 커서를 위치시킨다.
			FVector2D hitLoc = player->widgetInteractionComp->Get2DHitLocation();
			CursorRight->SetVisibility(ESlateVisibility::HitTestInvisible);
			CursorRight->SetRenderTranslation(hitLoc);
		}
		else
		{
			CursorRight->SetVisibility(ESlateVisibility::Hidden);
		}
		// 플레이어의 Widget Interaction Component가 위젯과 닿아있다면
		bool bIsCursorOnLeft = player->widgetInteractionCompLeft->IsOverHitTestVisibleWidget();
		if(bIsCursorOnLeft)
		{
			// 커서를 보이게 하고, 닿은 2D 위치값으로 커서를 위치시킨다.
			FVector2D hitLocLeft = player->widgetInteractionCompLeft->Get2DHitLocation();
			CursorLeft->SetVisibility(ESlateVisibility::HitTestInvisible);
			CursorLeft->SetRenderTranslation(hitLocLeft);
		}
		else
		{
			CursorLeft->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UTabletWidget::OpenStore()
{
	if(gi->checkDayCount == 0)
	{
		bCheckTutorialOpen = true;
	}
	else
	{
		spawnmg->SpawnCustomer();

		btn_OpenStore->SetIsEnabled(false);
	}
}

void UTabletWidget::CloseStore()
{
	if(gi->checkDayCount == 0)
	{
		bCheckTutorialClose = true;
	}
	else
	{
		spawnmg->SpawnOldPal();
	}
}

void UTabletWidget::OpenInternet()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(10);

	bCheckTutorialInternet = true;
}

void UTabletWidget::OpenMenuPage()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(0);
}

void UTabletWidget::OpenRecipePage()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(1);

	bCheckTutorialRecipe = true;
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

void UTabletWidget::CastToPlayerCharacter()
{
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
}

void UTabletWidget::OpenInbox()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(11);

	bCheckTutorialMail = true;
}

void UTabletWidget::OpenInMail1()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(12);
}

void UTabletWidget::OpenInMail2()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(13);
}

void UTabletWidget::OpenInMail3()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(14);
}

void UTabletWidget::OpenOutbox()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(15);
}

void UTabletWidget::OpenOutMail1()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(16);
}

void UTabletWidget::OpenOutMail2()
{
	WidgetSwitcher_Tablet->SetActiveWidgetIndex(17);
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
