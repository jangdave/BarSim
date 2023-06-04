// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CupBase.h"
#include "MartiniCup.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API AMartiniCup : public ACupBase
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void LiquorScale() override;

	virtual void AddIce(UPrimitiveComponent* OverlappedComponentM, AActor* OtherActorM, UPrimitiveComponent* OtherCompM, int32 OtherBodyIndexM, bool bFromSweepM, const FHitResult& SweepResultM) override;

	UPROPERTY()
	class AOlivePick* olive;

	UPROPERTY()
	class AIceCube* iceCubeM;
	UPROPERTY()
	class ASlicedLime* slicedLimeM;
	UPROPERTY()
	class AHalfSlicedLime* halfSlicedLimeM;

};
