// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "Coaster.generated.h"

UCLASS()
class BARSIM_API ACoaster : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoaster(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category=Coaster)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category=Coaster)
	class UStaticMeshComponent* staticMeshComp;

	UPROPERTY()
	bool isDropSoundEnabled = false;

	UFUNCTION()
	void SetSimulateAndTickDisable();

	UPROPERTY()
	FTimerHandle simHandle;

	UFUNCTION()
	void SimulateAndTickDisable();
};
