// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "BarSpoon.generated.h"

UCLASS()
class BARSIM_API ABarSpoon : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarSpoon(const FObjectInitializer& ObjectInitializer);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spoon")
	class UStaticMeshComponent* meshComp;

	UFUNCTION()
	void OnFluidOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	class ACupBase* cup;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spoon")
	bool bCupOverlapped = false;

	UFUNCTION()
	void OffFluidOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimeline timeline;

	UPROPERTY(EditAnywhere, Category = "Spoon")
	UCurveFloat* rotCurve;

	UFUNCTION()
	void TurnSpoon(float Output);

	UPROPERTY()
	bool isDropSoundEnabled = false;
};
