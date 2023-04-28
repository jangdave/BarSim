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

public:
	virtual void LiquorScale() override;
};
