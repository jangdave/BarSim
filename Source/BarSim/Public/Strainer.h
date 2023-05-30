// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "Strainer.generated.h"

UCLASS()
class BARSIM_API AStrainer : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStrainer(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Strainer")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "Strainer")
	bool isGlassStrainerAttachable=false;

	UFUNCTION()
	void AttachToMixingGlass();

	UPROPERTY()
	class AMixingGlass* mixingGlass;

	bool isMixingGlassCasted=  false;
	int32 mixingGlassArrayNum = 0;

	UPROPERTY()
	bool isDropSoundEnabled = false;

	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* attachSound;
};
