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
	ORDERJUDGE,
	HOLDCUP,
	DRINK,
	TASTEJUDGE,
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

	// 의자 순서 저장 인자
	UPROPERTY()
	int32 idx;

	// 주문 저장 인자
	UPROPERTY()
	int32 orderIdx;

	// 시간
	float curTime;

	// 애니메이션 플레이 여부
	bool bCheckPlayAnim;

	class AAIController* ai;

	// 주문 칵테일 정하기
	void SetOrderCoctail();
	
	// 상태 전환 함수
	UFUNCTION()
	void SetState(ECustomerState next);

	UFUNCTION()
	void SetSitState(ECustomerSitState next);

	UFUNCTION()
	void SetDrinkState(ECustomerDrinkState next);

	// 주문내역 보이는 함수
	void VisibleOrder();

	// 손님 의자에 붙이기
	UFUNCTION()
	void AttachCustomer();

	// 손님 의자에서 떨어트리기
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

	void TickOrderJudge();
	
	void TickHoldCup();
	
	void TickDrink();

	void TickTasteJudge();
	
	void TickAngry();

	void TickAwesome();

	// drink 상태 함수
	void TickIdleCup();
	
	void TickDrinkCup();

	void TickUnHoldCup();
		
};
