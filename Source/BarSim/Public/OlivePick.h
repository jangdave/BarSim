// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OlivePick.generated.h"

UCLASS()
class BARSIM_API AOlivePick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOlivePick();

	UPROPERTY(EditAnywhere, Category = "Olive")
	class UStaticMeshComponent* oliveComp;

	UPROPERTY()
	bool isOliveAttachable = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
