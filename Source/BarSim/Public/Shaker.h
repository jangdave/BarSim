// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CupBase.h"
#include "Shaker.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API AShaker : public ACupBase
{
	GENERATED_BODY()
	AShaker(const FObjectInitializer& ObjectInitializer);
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void LiquorScale() override;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	class UWidgetComponent* widgetComp2;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	FVector upVector = FVector(0,0,1);

	UPROPERTY(EditAnywhere, Category = "Shaker")
	class UNiagaraSystem* streamFX;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	class UNiagaraComponent* waterStream;

	bool bStreamOn = false;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	TSubclassOf<class ADropBase> streamDrop;

	UPROPERTY()
	FVector startPos;

	UPROPERTY()
	FVector newPos;

	UPROPERTY()
	FVector startVelocity;

	UPROPERTY()
	FVector newVelocity;

	UPROPERTY()
	FVector startAcc;

	UPROPERTY()
	FVector newAcc;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	float shakeAcc = 2300.0f;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	bool bShaking;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	float shakingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shaker")
	float acc;	
	
	UPROPERTY(EditAnywhere, Category = "Shaker")
	class AShakerStrainer* strainer;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	bool bStrainerOn;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	bool bLidOn;

	UFUNCTION()
	void Shake();
	
	virtual void CupStop() override;

	//UPROPERTY()
	//bool isDropSoundEnabledS = false;

	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* pourSoundS;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* pourStopSoundS;

	UPROPERTY()
	bool pourSoundBoolean = false;

	UPROPERTY()
	class UAudioComponent* pourSoundAudioCompS;

	UPROPERTY()
	bool isGrabbingShaker=false;

	//쉐이크 위젯 관련

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	bool bShakeWidgetOn;

	UPROPERTY()
	class UShakeWidget* shakeWidget;

	UPROPERTY()
	float widgetTime2;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	bool bShakeWidgetAnimOn;
	
};

