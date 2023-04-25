// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class BARSIM_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void SpawnCustom();

	UPROPERTY()
	TArray<AActor*> chairs;

	UPROPERTY()
	TArray<bool> bIsSit;

	UPROPERTY()
	TArray<bool> bIsCoctail;

	UPROPERTY()
	TArray<bool> bIsCoaster;
	
	UPROPERTY()
	TArray<bool> bIsPlayer;
	
	bool bCheckSit;

	int32 checkCustomerNum;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACustomerCharacter> customerFactory;

	void CheckArray();

	void CheckChairSit();
};
