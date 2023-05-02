// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TabletWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UTabletWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	class ASpawnManager* spawnmg;
	
	// 테블렛 상단바
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* PB_Reputation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* text_Time;

	// 위젯스위처
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Tablet;

	// 테블렛 메뉴
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_OpenStore;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_CloseStore;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Recipe;

	// 테블릿 레시피 메뉴
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_BackMenu;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_OpenGinLime;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_OpenGinLimeVideo;
	
	// 테블릿 진라임 레시피 & 영상
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_BackRecipeMenu0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_BackRecipeMenu1;

	UFUNCTION()
	void OpenStore();

	UFUNCTION()
	void CloseStore();

	UFUNCTION()
	void OpenMenuPage();
	
	UFUNCTION()
	void OpenRecipePage();

	UFUNCTION()
	void OpenGinLime();

	UFUNCTION()
	void OpenGinLimeVideo();
	
};