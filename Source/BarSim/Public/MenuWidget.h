// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class AMenuWidgetActor* menuActor;

	UPROPERTY()
	class UBarGameInstance* gi;
	
	// 위젯스위처
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Menu;

	// 메뉴 버튼
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_StoryMode;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_QuitGame;

	// 모드 선택
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_TutorialYes;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_TutorialNo;

	// 메뉴 스폰
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_ResumeGame;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_ResetGame;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_QuitGame1;

	// 0일차 메뉴 함수
	UFUNCTION()
	void GameStart();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void StoryMode();

	UFUNCTION()
	void TutorialMode();

	// 이후 메뉴 함수
	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void ResetGame();
};
