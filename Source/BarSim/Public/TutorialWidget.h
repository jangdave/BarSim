// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Tutorial;

	UFUNCTION()
	void SetWelcome();

	UFUNCTION()
	void SetFirst();

	UFUNCTION()
	void SetSecond();

	UFUNCTION()
	void SetThird();
	
	UFUNCTION()
	void SetFourth();

	UFUNCTION()
	void SetCheckCup();
	
	//-----------------------------------------------------------------first
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFirst1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFirst2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFirst3;

	UFUNCTION()
	void SetFirst1Check();

	UFUNCTION()
	void SetFirst1UnCheck();
	
	UFUNCTION()
	void SetFirst2Check();

	UFUNCTION()
	void SetFirst2UnCheck();

	UFUNCTION()
	void SetFirst3Check();

	UFUNCTION()
	void SetFirst3UnCheck();
	
	//-----------------------------------------------------------------second
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkSecond1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkSecond2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkSecond3;

	UFUNCTION()
	void SetSecond1Check();
	
	UFUNCTION()
	void SetSecond1UnCheck();

	UFUNCTION()
	void SetSecond2Check();
	
	UFUNCTION()
	void SetSecond2UnCheck();

	UFUNCTION()
	void SetSecond3Check();

	UFUNCTION()
	void SetSecond3UnCheck();
	
	//-----------------------------------------------------------------third


	//-----------------------------------------------------------------fourth




};
