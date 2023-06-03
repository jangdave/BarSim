// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropSoundCollision.generated.h"

UCLASS()
class BARSIM_API ADropSoundCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropSoundCollision();

	UPROPERTY(EditAnywhere, Category="CollSettings")
	class UBoxComponent* boxComp;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// References
	UPROPERTY()
	class AHuchuTong* huchuTong;
	UPROPERTY()
	class ABottleBase* bottle;
	UPROPERTY()
	class ATablet* tablet;
	UPROPERTY()
	class ACoaster* coaster;
	UPROPERTY()
	class ACupBase* cup;
	UPROPERTY()
	class AIceCube* iceCube;
	UPROPERTY()
	class ABarSpoon* barSpoon;
	UPROPERTY()
	class AShakerLid* shakerLid;
	UPROPERTY()
	class AStrainer* strainer;
	UPROPERTY()
	class AShakerStrainer* shakerStrainer;
	UPROPERTY()
	class AShaker* shaker;
	UPROPERTY()
	class AMixingGlass* mixingGlass;
	UPROPERTY()
	class ASlicedLime* slicedLime;
	UPROPERTY()
	class AHalfSlicedLime* halfSlicedLime;
	UPROPERTY()
	class ADrinkCan* drinkCan;

	// Sounds
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* huchuTongDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* bottleDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* tabletDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* coasterDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* cupDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* iceCubeDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* barSpoonDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* shakerLidDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* strainerDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* shakerStrainerDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* shakerDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* mixingGlassDropSound;
	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* canDropSound;;

	UPROPERTY(EditAnywhere, Category="Sounds")
	float soundVolume = 0.7;
};
