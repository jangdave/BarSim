// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropBase.h"
#include "MixedDrop.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API AMixedDrop : public ADropBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "MixedDrop")
	TArray<FString> NameArray;

	UPROPERTY(VisibleAnywhere, Category = "MixedDrop")
	TArray<float> ContentsArray;

	UPROPERTY(VisibleAnywhere, Category = "MixedDrop")
	bool bMixed;
};
