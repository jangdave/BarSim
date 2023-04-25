// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropBase.h"
#include "GinDrop.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API AGinDrop : public ADropBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;;
};
