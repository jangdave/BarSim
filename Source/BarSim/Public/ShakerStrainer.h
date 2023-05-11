// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "ShakerStrainer.generated.h"

UCLASS()
class BARSIM_API AShakerStrainer : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShakerStrainer(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "ShakerStrainer")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "ShakerStrainer")
	class USplineComponent* splineComp;

	UPROPERTY(EditAnywhere, Category = "ShakerStrainer")
	class USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere, Category = "ShakerStrainer")
	FVector streamPoint;

	UFUNCTION()
	void LidOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LidOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY()
	class AShakerLid* lid;

	UPROPERTY(EditAnywhere, Category = "ShakerStrainer")
	bool bLidOn;
};