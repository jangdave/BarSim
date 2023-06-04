// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CupBase.h"
#include "RockGlass.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API ARockGlass : public ACupBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY()
	class AOlivePick* olive;

	UPROPERTY()
	class AHalfSlicedOrange* HalfSlicedOrange;

	UPROPERTY()
	class ASlicedOrange* SlicedOrange;

	UPROPERTY()
	class AIceCube* iceCubeR;

	UPROPERTY()
	class ASlicedOrange* slicedOrangeR;

	UPROPERTY()
	class AHalfSlicedOrange* halfSlicedOrangeR;
	
};
