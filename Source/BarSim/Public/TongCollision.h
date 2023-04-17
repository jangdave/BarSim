// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TongCollision.generated.h"

UCLASS()
class BARSIM_API ATongCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATongCollision();


	UPROPERTY(EditAnywhere, Category="TongColSettings")
	class UBoxComponent* tongCol;

	UPROPERTY()
	FVector compScale;
	UPROPERTY()
	FVector actorScale;

	UPROPERTY(EditAnywhere)
	class AHuchuTong* huchuTongRef;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
