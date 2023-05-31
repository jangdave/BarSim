// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grippables/GrippableActor.h"
#include "SlicedLime.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API ASlicedLime : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlicedLime(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category=IceSettings)
	class UStaticMeshComponent* limeMesh;

	UPROPERTY()
	bool isSlicedLimeAttachable = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
