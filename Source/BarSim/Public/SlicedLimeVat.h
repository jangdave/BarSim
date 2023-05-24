// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlicedLimeVat.generated.h"

UCLASS()
class BARSIM_API ASlicedLimeVat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlicedLimeVat();

	UPROPERTY(EditAnywhere, Category = "LimeVat")
	class UStaticMeshComponent* meshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
