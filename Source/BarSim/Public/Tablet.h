// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "Tablet.generated.h"

UCLASS()
class BARSIM_API ATablet : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATablet(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, Category=tabletSettings)
	class UStaticMeshComponent* tabletMesh;

	UPROPERTY(EditAnywhere, Category=tabletSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=tabletSettings)
	class UWidgetComponent* widgetComp;

	UPROPERTY(EditAnywhere)
	class UTabletWidget* tablet_UI;

//class ABarPlayer* player;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	bool isDropSoundEnabled = false;

	UPROPERTY()
	class ATabletStand* tabletStand;

	UFUNCTION()
	void AttachToTabletStand();

	UPROPERTY()
	bool isTabletStandCasted = false;

	UPROPERTY()
	int32 tabletStandArrayNum = 0;

	UPROPERTY(EditAnywhere, Category="Sounds")
	class USoundBase* attachSound;
	
	UFUNCTION()
	void SetSimulateAndTickDisable();

	UPROPERTY()
	FTimerHandle simHandle;

	UFUNCTION()
	void SimulateAndTickDisable();

};
