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

	// 몽타주 섹션 플레이 함수
	UFUNCTION()
	void OnStandAnim(float sectionTime);

	UFUNCTION()
	void OnLeanAnim(float sectionTime);

	UFUNCTION()
	void OnSitAnim(float sectionTime);

	UFUNCTION()
	void OnDrinkAnim(float sectionTime);

	// 몽타주 엔딩 연결 함수
	UFUNCTION(BlueprintCallable)
	void EndLean();

	UFUNCTION(BlueprintCallable)
	void EndSitStoll();
	
	UFUNCTION(BlueprintCallable)
	void EndTalk();

	UFUNCTION(BlueprintCallable)
	void EndUnLean();

	UFUNCTION(BlueprintCallable)
	void EndHoldCup();

	UFUNCTION(BlueprintCallable)
	void AttachCup();

	UFUNCTION(BlueprintCallable)
	void EndCheer();

	UFUNCTION(BlueprintCallable)
	void EndDrinkLittle();
	
	UFUNCTION(BlueprintCallable)
	void EndDrinkAll();

	UFUNCTION(BlueprintCallable)
	void DetachCup();
	
	UFUNCTION(BlueprintCallable)
	void EndUnHoldCup();

	UFUNCTION(BlueprintCallable)
	void EndLeaveSit();
};
