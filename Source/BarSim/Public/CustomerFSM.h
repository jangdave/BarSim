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
	DRINK,
	JUDGEMENT,
	ANGRY,
	AWESOME,
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

	bool bCheckEndAnim;

	class AAIController* ai;

	UFUNCTION()
	void SetState(ECustomerState next);

	UFUNCTION()
	void SetSitState(ECustomerSitState next);

	void LookPlayer();

	void LookOrder();
	
private:
	void TickIdle();

	void TickMove();

	void TickSit();

	void TickLeave();

	void TickStandby();

	void TickStandbyWaitLong();
	
	void TickOrder();

	void TickWait();

	void TickWaitLong();
	
	void TickDrink();

	void TickJudgement();
	
	void TickAngry();

	void TickAwesome();
		
};
