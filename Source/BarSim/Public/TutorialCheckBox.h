// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialCheckBox.generated.h"

UCLASS()
class BARSIM_API ATutorialCheckBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialCheckBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* checkBoxComp;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* playerStandComp;

	UPROPERTY()
	class ATutorialManager* tutorialManager;
	
	UFUNCTION()
	void FirstStageStart();
	
	UFUNCTION()
	void FirstStage();

	UFUNCTION()
	void SecondStageStart();

	UFUNCTION()
	void SecondStage();
	
	UFUNCTION()
	void ThirdStageStart();

	UFUNCTION()
	void ThirdStage();

	UFUNCTION()
	void FourthStageStart();
	
	UFUNCTION()
	void FourthStage();

	UPROPERTY()
	bool bCheckPlayerOnce;
};
