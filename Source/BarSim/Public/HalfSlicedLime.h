// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlicedLime.h"
#include "HalfSlicedLime.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API AHalfSlicedLime : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHalfSlicedLime(const FObjectInitializer& ObjectInitializer);	
	
	UPROPERTY(EditAnywhere, Category=IceSettings)
	class UStaticMeshComponent* limeMesh;
	
};
