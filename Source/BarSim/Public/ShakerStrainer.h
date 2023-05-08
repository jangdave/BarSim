// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShakerStrainer.generated.h"

UCLASS()
class BARSIM_API AShakerStrainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShakerStrainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "Shaker")
	class USplineComponent* splineComp;

	UPROPERTY(VisibleAnywhere, Category = "Shaker")
	FVector streamPoint;
};


