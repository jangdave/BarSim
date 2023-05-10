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

	UFUNCTION()
	void StrainerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StrainerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY()
	class AStrainer* strainer;
};