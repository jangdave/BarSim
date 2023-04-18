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
	ORDER,
	WAIT,
	WAITLONG,
	DRINK,
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

	int32 idx;

	float curTime;
	
	class AAIController* ai;

	void SetState(ECustomerState next);

	void SetSitState(ECustomerSitState next);
	
private:
	void TickIdle();

	void TickMove();

	void TickSit();

	void TickLeave();

	void TickOrder();

	void TickWait();

	void TickWaitLong();
	
	void TickDrink();
	
	void TickAngry();

	void TickAwesome();
		
};
