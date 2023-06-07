// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "SlicedLimeVat.generated.h"

UCLASS()
class BARSIM_API ASlicedLimeVat : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlicedLimeVat(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "LimeVat")
	class UStaticMeshComponent* meshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	bool isDropSoundEnabled = false;

	UFUNCTION()
	void SetSimulateAndTickDisable();

	UPROPERTY()
	FTimerHandle simHandle;

};
