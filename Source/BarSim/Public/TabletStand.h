// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TabletStand.generated.h"

UCLASS()
class BARSIM_API ATabletStand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATabletStand();

	UPROPERTY(EditAnywhere, Category = "TabletStand")
	class UStaticMeshComponent* meshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
