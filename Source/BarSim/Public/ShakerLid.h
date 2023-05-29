// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "ShakerLid.generated.h"


UCLASS()
class BARSIM_API AShakerLid : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShakerLid(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Lid")
	class UStaticMeshComponent* meshComp;

	UFUNCTION()
	void AttachToShakerStrainer();

	UPROPERTY()
	class AShakerStrainer* shakerStrainer;

	UPROPERTY()
	bool isShakerStrainerCasted = false;

	int32 StrainerArrayNum = 0;

	UPROPERTY()
	bool isDropSoundEnabled = false;

	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* attachSound;
	
};
