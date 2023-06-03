// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grippables/GrippableActor.h"
#include "DrinkCan.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API ADrinkCan : public AGrippableActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool isDropSoundEnabled = false;
};
