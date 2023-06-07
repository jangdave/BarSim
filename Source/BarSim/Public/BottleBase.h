// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "BottleBase.generated.h"

UCLASS()
class BARSIM_API ABottleBase : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABottleBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bottle")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bottle")
	class UStaticMeshComponent* pourer;

	UPROPERTY(VisibleAnywhere, Category = "Bottle")
	FVector upVector = FVector(0,0,1);

	UPROPERTY(EditAnywhere, Category = "Bottle")
	class UNiagaraSystem* streamFX;
	
	UPROPERTY(VisibleAnywhere, Category = "Bottle")
	class UNiagaraComponent* waterStream;	

	bool bStreamOn = false;

	UPROPERTY(EditAnywhere, Category = "Bottle")
	float maxContents = 25.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bottle")
	float remains;

	//UPROPERTY(EditAnywhere, Category = "Bottle")
	//TSubclassOf<class ADropBase> liquorDrop;

	UPROPERTY(EditAnywhere, Category = "Bottle")
	TSubclassOf<class ADropBase> streamDrop;

	UPROPERTY()
	bool isDropSoundEnabled = false;

	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* pourSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* pourStopSound;

	UPROPERTY()
	bool pourSoundBoolean = false;

	UPROPERTY()
	class UAudioComponent* pourSoundAudioComp;

	UPROPERTY()
	bool isGrabbingBottle=false;

	UPROPERTY()
	bool isGBR = false;
	UPROPERTY()
	bool isGBL =false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* glassClankAudioComp;

	// Player Controller
	UPROPERTY()
	class APlayerController* PC;

	UPROPERTY(EditDefaultsOnly, Category="Haptics")
	class UHapticFeedbackEffect_Curve* HF_PourLiquid;

	UFUNCTION()
	void SetSimulateAndTickDisable();

	UPROPERTY()
	FTimerHandle simHandle;
};
