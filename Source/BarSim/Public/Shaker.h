// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CupBase.h"
#include "Shaker.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API AShaker : public ACupBase
{
	GENERATED_BODY()
	AShaker(const FObjectInitializer& ObjectInitializer);
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void LiquorScale() override;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	class USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	FVector upVector = FVector(0,0,1);

	UPROPERTY(EditAnywhere, Category = "Shaker")
	class UNiagaraSystem* streamFX;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	class UNiagaraComponent* waterStream;

	bool bStreamOn = false;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	TSubclassOf<class ADropBase> streamDrop;

	UPROPERTY()
	FVector startPos;

	UPROPERTY()
	FVector newPos;

	UPROPERTY()
	FVector startVelocity;

	UPROPERTY()
	FVector newVelocity;

	UPROPERTY()
	FVector startAcc;

	UPROPERTY()
	FVector newAcc;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	float shakeAcc = 2300.0f;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	bool bShaking;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	float shakingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shaker")
	float acc;

	UFUNCTION()
	void StrainerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StrainerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, Category = "Shaker")
	class AShakerStrainer* strainer;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	bool bStrainerOn;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	bool bLidOn;
};

