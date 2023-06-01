// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CupBase.h"
#include "MixingGlass.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API AMixingGlass : public ACupBase
{
	GENERATED_BODY()
	AMixingGlass(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "MixingGlass")
	FVector upVector = FVector(0,0,1);

	UPROPERTY(EditAnywhere, Category = "MixingGlass")
	class UNiagaraSystem* streamFX;

	UPROPERTY(VisibleAnywhere, Category = "MixingGlass")
	class UNiagaraComponent* waterStream;

	bool bStreamOn = false;

	UPROPERTY(EditAnywhere, Category = "MixingGlass")
	TSubclassOf<class ADropBase> streamDrop;

	UPROPERTY(EditAnywhere, Category = "MixingGlass")
	bool bStrainerOn;

	UPROPERTY(EditAnywhere, Category = "MixingGlass")
	class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, Category = "MixingGlass")
	class USphereComponent* stirChecker1;

	UPROPERTY(EditAnywhere, Category = "MixingGlass")
	class USphereComponent* stirChecker2;
	
	UPROPERTY()
	class AStrainer* strainer;
	
	virtual void CupStop() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MixingGlass")
	class UWidgetComponent* widgetComp2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MixingGlass")
	bool bStirWidgetOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MixingGlass")
	bool bStirWidgetAnimOn;

	UFUNCTION()
	void Stir(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	class ABarSpoon* spoon;

	UPROPERTY()
	class UStirWidget* stirWidget;

	UPROPERTY(VisibleAnywhere, Category = "MixingGlass")
	bool bIsStirStarted;

	UPROPERTY(VisibleAnywhere, Category = "MixingGlass")
	float widgetTime2;

	UPROPERTY(EditAnywhere, Category = "MixingGlass")
	class USoundBase* stirSound;
	
	//UPROPERTY()
	//bool isDropSoundEnabledM = false;

	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* pourSoundM;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* pourStopSoundM;

	UPROPERTY()
	bool pourSoundBoolean = false;

	UPROPERTY()
	class UAudioComponent* pourSoundAudioCompM;

	UPROPERTY()
	bool isGrabbingMixingGlass=false;
};