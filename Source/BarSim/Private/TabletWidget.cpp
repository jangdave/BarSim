// Fill out your copyright notice in the Description page of Project Settings.


#include "TabletWidget.h"
#include "SpawnManager.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UTabletWidget::NativeConstruct()
{
	Super::NativeConstruct();

	spawnmg = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));

	// 테블렛 메뉴
	btn_OpenStore->OnClicked.AddDynamic(this, &UTabletWidget::OpenStore);
	btn_CloseStore->OnClicked.AddDynamic(this, &UTabletWidget::CloseStore);
	btn_CloseStore->SetIsEnabled(false);
	btn_Recipe->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	// 테블릿 레시피 메뉴
	btn_BackMenu->OnClicked.AddDynamic(this, &UTabletWidget::OpenMenuPage);
	btn_OpenGinLime->OnClicked.AddDynamic(this, &UTabletWidget::OpenGinLime);
	btn_OpenGinLimeVideo->OnClicked.AddDynamic(this, &UTabletWidget::OpenGinLimeVideo);
	// 테블릿 진라임 레시피 & 영상
	btn_BackRecipeMenu0->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);
	btn_BackRecipeMenu1->OnClicked.AddDynamic(this, &UTabletWidget::OpenRecipePage);



	WidgetSwitcher_Tablet->SetActiveWidgetIndex(7);
}

void UTabletWidget::OpenStore()
{
	spawnmg->SpawnCustomer();
}

void UTabletWidget::CloseStore()
{
	spawnmg->SpawnOldPal();
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
