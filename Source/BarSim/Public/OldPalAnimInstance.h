// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OldPalFSM.h"
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

	// fsm에서 받아오는 oldpal 상태
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EOldPalState ownerState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EOldPalSitState ownerSitState;

	// 몽타주
	UPROPERTY(EditAnywhere)
	class UAnimMontage* oldPalMontageFactory;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* oldPalLeanMontageFactory;
	
	UPROPERTY(EditAnywhere)
	class UAnimMontage* oldPalSitMontageFactory;
	
	UPROPERTY(EditAnywhere)
	class UAnimMontage* oldPalDrinkMontageFactory;
	
	UFUNCTION()
	void OnStandAnim(float sectionTime);

	UFUNCTION()
	void OnLeanAnim(float sectionTime);

	UFUNCTION()
	void OnSitAnim(float sectionTime);

	UFUNCTION()
	void OnDrinkAnim(float sectionTime);

	UFUNCTION(BlueprintCallable)
	void EndLean();

	UFUNCTION(BlueprintCallable)
	void EndTalk();

	UFUNCTION(BlueprintCallable)
	void EndUnLean();

	UFUNCTION(BlueprintCallable)
	void EndSitStoll();
};
