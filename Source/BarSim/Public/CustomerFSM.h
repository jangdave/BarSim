// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomerFSM.generated.h"

UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	IDLE,
	MOVE,
	READYSIT,
	SIT,
	LEAVE,
};

UENUM(BlueprintType)
enum class ECustomerSitState : uint8
{
	STANDBY,
	STANDBYWAITLONG,
	ORDER,
	WAIT,
	WAITLONG,
	HOLDCUP,
	DRINK,
	JUDGEMENT,
	ANGRY,
	AWESOME,
};

UENUM(BlueprintType)
enum class ECustomerDrinkState : uint8
{
	IDLE,
	DRINK,
	UNHOLDCUP,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BARSIM_API UCustomerFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomerFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 손님 기본 상태
	ECustomerState state;

	// 손님 착석 상태
	ECustomerSitState sitState;

	// 손님 마시기 상태
	ECustomerDrinkState drinkState;
	
	UPROPERTY()
	class ACustomerCharacter* owner;

	UPROPERTY()
	class ASpawnManager* spawnManager;

	UPROPERTY()
	class ABarPlayer* player;

	UPROPERTY()
	int32 idx;

	UPROPERTY()
	int32 orderIdx;
	
	float curTime;

	bool bCheckPlayAnim;

	class AAIController* ai;

	// 상태 전환 함수
	UFUNCTION()
	void SetState(ECustomerState next);

	UFUNCTION()
	void SetSitState(ECustomerSitState next);

	UFUNCTION()
	void SetDrinkState(ECustomerDrinkState next);
	
	void VisibleOrder();

	// 손님 의자에 붙이고 떨어트리기
	UFUNCTION()
	void AttachCustomer();

	UFUNCTION()
	void DetachCustomer();

	// 랜덤 함수
	int32 SetRandRange(int32 idxStart, int32 idxEnd);
	
private:
	// 기본 상태 함수
	void TickIdle();

	void TickMove();

	void TickReadySit();

	void TickSit();

	void TickLeave();

	// sit 상태 함수
	void TickStandby();

	void TickStandbyWaitLong();
	
	void TickOrder();

	void TickWait();

	void TickWaitLong();
	
	void TickHoldCup();
	
	void TickDrink();

	void TickJudgement();
	
	void TickAngry();

	void TickAwesome();

	// drink 상태 함수
	void TickIdleCup();
	
	void TickDrinkCup();

	void TickUnHoldCup();
		
};
