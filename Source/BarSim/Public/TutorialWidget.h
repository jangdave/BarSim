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

	UFUNCTION()
	void SetCheckTablet();
	
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
	void SetFirst3Check();
	
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
	void SetSecond2Check();
	
	UFUNCTION()
	void SetSecond3Check();

	//-----------------------------------------------------------------third
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkThird1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkThird2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkThird3;

	UFUNCTION()
	void SetThird1Check();

	UFUNCTION()
	void SetThird2Check();

	UFUNCTION()
	void SetThird3Check();

	//-----------------------------------------------------------------fourth

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFourth1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFourth2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFourth3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFourth4;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UCheckBox* checkFourth5;
	
	UFUNCTION()
	void SetFourth1Check();

	UFUNCTION()
	void SetFourth2Check();

	UFUNCTION()
	void SetFourth3Check();

	UFUNCTION()
	void SetFourth4Check();

	UFUNCTION()
	void SetFourth5Check();
	
};
