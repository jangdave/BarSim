// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chair.h"
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
	
	UPROPERTY()
	TArray<AActor*> chairs;

	UPROPERTY()
	TArray<AChair*> aChairs;

	// 의자 비어있는지 bool 배열
	UPROPERTY()
	TArray<bool> bIsSit;

	// 의자마다 칵테일이 있는지 bool 배열
	UPROPERTY()
	TArray<bool> bIsCoctail;

	// 의자마다 코스터가 있는지 bool 배열
	UPROPERTY()
	TArray<bool> bIsCoaster;

	// 플레이어가 있는지 여부
	UPROPERTY()
	TArray<bool> bIsPlayer;

	UPROPERTY()
	TArray<int32> orderCoctailIdx = {0, 0, 0};
	
	bool bCheckSit;

	int32 checkCustomerNum;
	
	UPROPERTY()
	int32 checkMeshCount = 3;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACustomerCharacter> customerFactory;

	void CheckChairSit();
	
	void CheckArray();
	
	UFUNCTION()
	void SpawnCustomer();
	
	void SpawnCustom();

	UFUNCTION()
	void GetCustomerIdx(int32 orderIdx, int32 idx);

	UFUNCTION()
	void AllOut();

	UFUNCTION()
	void SpawnOldPal();

	// 점수 체크------------------------------------------------------------------------------------
public:
	void GetCup(TArray<FString> cocName, TArray<float> cocLiter, bool bStirred, bool bStirredLater, bool bShake, int32 customerIdx);

	TArray<FString> GinLime = {"Gin", "Lime"};

	TArray<FString> Martini = {"Gin", "Vermouth"};

	TArray<FString> OldPal = {"Whisky", "Vermouth", "Campari"};

	TArray<FString> Daiquiri = {"Rum", "Lime"};
	
	float amountOfRum;

	float amountOfGin;

	float amountOfWhisky;

	float amountOfLime;
	
	float amountOfVermouth;
	
	float amountOfCampari;

	int32 orderScore = 100;
	
	void CheckGin(TArray<FString> cocName, bool bStirred, bool bStirredLater, int32 customerIdx);

	void CheckWhisky(TArray<FString> cocName, bool bStirred, bool bStirredLater, int32 customerIdx);

	void CheckRum(TArray<FString> cocName, bool bStirred, bool bStirredLater, bool bShake, int32 customerIdx);

	void CheckGinLime(int32 customerIdx);

	void CheckMartini(int32 customerIdx);

	void CheckOldPal(int32 customerIdx);

	void CheckDaiquiri(int32 customerIdx);

	void SomethingElse(int32 customerIdx);
	
};
