// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "IceCubeVat.generated.h"

UCLASS()
class BARSIM_API AIceCubeVat : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceCubeVat(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "IceVat")
	class UStaticMeshComponent* meshComp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	bool isDropSoundEnabled = false;

};
