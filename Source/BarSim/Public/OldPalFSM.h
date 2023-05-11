// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OldPalFSM.generated.h"

UENUM(BlueprintType)
enum class EOldPalState : uint8
{
	IDLE,
	MOVE,
	READYSIT,
	SIT,
	LEAVE,
};

UENUM(BlueprintType)
enum class EOldPalSitState : uint8
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
	READYLEAVE,
};

UENUM(BlueprintType)
enum class EOldPalDrinkState : uint8
{
	IDLE,
	DRINK,
	UNHOLDCUP,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BARSIM_API UOldPalFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOldPalFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 올드팔 기본 상태
	EOldPalState state;

	// 올드팔 착석 상태
	EOldPalSitState sitState;

	// 올드팔 마시기 상태
	EOldPalDrinkState drinkState;
	
	UPROPERTY()
	class AOldPalCharacter* owner;

	UPROPERTY()
	class ASpawnManager* spawnManager;
	
	class AAIController* ai;

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

	// 주문 실패시 기회 소모 여부
	bool bCheckOrder;
	
	// 주문 칵테일 정하기
	void SetOrderCoctail();
	
	// 상태 전환 함수
	UFUNCTION()
	void SetState(EOldPalState next);

	UFUNCTION()
	void SetSitState(EOldPalSitState next);

	UFUNCTION()
	void SetDrinkState(EOldPalDrinkState next);

	// 주문내역 보이는 함수
	void VisibleOrder();

	// 손님 의자에 붙이기
	UFUNCTION()
	void AttachCustomer();

	// 손님 의자에서 떨어트리기
	UFUNCTION()
	void DetachCustomer();

	// 랜덤 함수
	UFUNCTION()
	int32 SetRandRange(int32 idxStart, int32 idxEnd);

	// 마신 횟수
	UPROPERTY()
	int32 drinkCount = 0;
	
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

	void TickReadyLeave();

	// drink 상태 함수
	void TickIdleCup();
	
	void TickDrinkCup();

	void TickUnHoldCup();
		
};
