// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OldPalAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UOldPalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	class AOldPalCharacter* owner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float forwardVelocity;
	
	UPROPERTY(EditAnywhere)
	class UAnimMontage* oldPalMontageFactory;

	UFUNCTION()
	void OnSitAnim(FName sectionName);
};
