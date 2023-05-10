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

	UPROPERTY()
	int32 idx;

	UPROPERTY()
	int32 orderIdx;
};
