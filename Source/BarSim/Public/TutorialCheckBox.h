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

	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* tutorialWidget;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* tutorialBox;
	
	UPROPERTY(EditAnywhere)
	class UTutorialWidget* tutorial_UI;
	
	UPROPERTY()
	class ATutorialManager* tutorialManager;

	UPROPERTY()
	class UBarGameInstance* gi;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* checkSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* nextSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* levelSound;

	FTimerHandle timerFirst;

	FTimerHandle timerSecond;

	FTimerHandle timerThird;

	FTimerHandle timerFourth;
	
	UFUNCTION()
	void StartWelcome();
	
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

	UFUNCTION()
	void SetLanguage();

	UPROPERTY()
	bool bCheckPlayerOnce;

	UFUNCTION()
	void OnCheckOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
