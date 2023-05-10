// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CustomerFSM.h"
#include "CustomerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API UCustomerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	class ACustomerCharacter* owner;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float forwardVelocity;
	
	// fsm에서 받아오는 customer 상태
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECustomerState ownerState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECustomerSitState ownerSitState;
	
	// 몽타주
	UPROPERTY(EditAnywhere)
	class UAnimMontage* customerMontageFactory;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* customerSitMontageFactory;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* customerDrinkMontageFactory;

	// stand 상태 몽타주 플레이 함수
	UFUNCTION()
	void OnStandAnim(FName sectionName);

	// 스톨에 앉는 애니메이션 끝나고 이어지는 함수
	UFUNCTION(BlueprintCallable)
	void EndSitStoll();

	// sit 상태 몽타주 플레이 함수
	UFUNCTION()
	void OnSitAnim(FName sectionName);

	// 불만을 표출하는 애니메이션 끝나고 이어지는 함수
	UFUNCTION(BlueprintCallable)
	void EndWaitLong();

	// 주문을 하는 애니메이션 끝나고 이어지는 함수
	UFUNCTION(BlueprintCallable)
	void EndOrder();

	UFUNCTION(BlueprintCallable)
	void AttachCup();
	
	UFUNCTION(BlueprintCallable)
	void EndHoldCup();
	
	UFUNCTION(BlueprintCallable)
	void EndAngry();

	UFUNCTION(BlueprintCallable)
	void EndGood();

	UFUNCTION(BlueprintCallable)
	void EndLeaveSit();
	
	// drink 상태 몽타주 플레이 함수
	UFUNCTION()
	void OnDrinkAnim(FName sectionName);

	UFUNCTION(BlueprintCallable)
	void EndCheers();

	UFUNCTION(BlueprintCallable)
	void EndDrinkAllLittle();

	UFUNCTION(BlueprintCallable)
	void DetachCup();

	UFUNCTION(BlueprintCallable)
	void EndUnHoldCup();

};
