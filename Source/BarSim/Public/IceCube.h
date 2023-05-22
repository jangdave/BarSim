// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "IceCube.generated.h"

UCLASS()
class BARSIM_API AIceCube : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceCube(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category=IceSettings)
	class UStaticMeshComponent* iceCubeMesh;

	UPROPERTY(EditAnywhere, Category=IceSettings)
	class UBoxComponent* boxComp;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	bool isDropSoundEnabled = false;
};
