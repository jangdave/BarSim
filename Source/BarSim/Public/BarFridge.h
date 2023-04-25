// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BarFridge.generated.h"

UCLASS()
class BARSIM_API ABarFridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarFridge();

	UPROPERTY(EditDefaultsOnly, Category="FridgeSettings")
	class UStaticMeshComponent* barFridgeMesh;

	UPROPERTY(EditDefaultsOnly, Category="FridgeSettings")
	class UStaticMeshComponent* barFridgeDoorMesh;;
	
	UPROPERTY(EditDefaultsOnly, Category="FridgeSettings")
	class UPhysicsConstraintComponent* physicsConstraint;

	//UPROPERTY(EditDefaultsOnly, Category="FridgeSettings")
	//class UBoxComponent* doorGrabComp;



	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
