// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropBase.h"
#include "RumDrop.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API ARumDrop : public ADropBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
