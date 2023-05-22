// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialLight.generated.h"

UCLASS()
class BARSIM_API ATutorialLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Tutorial")
	class USpotLightComponent* spotLight;

	UPROPERTY(EditAnywhere, Category = "Tutorial")
	float lightIntensity = 0;
};
