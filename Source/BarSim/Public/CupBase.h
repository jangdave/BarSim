// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CupBase.generated.h"

UCLASS()
class BARSIM_API ACupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Cup")
	class UStaticMeshComponent* measureComp;

	UPROPERTY(EditAnywhere, Category = "Cup")
	class UStaticMeshComponent* liquorComp;

	UPROPERTY(EditAnywhere, Category = "Cup")
	class UStaticMeshComponent* igCheckerComp;

	UPROPERTY(EditAnywhere, Category = "Cup")
	class UStaticMeshComponent* cupComp;

	UFUNCTION()
	void AddLiquor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void ExtractIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Cup")
	class ADropBase* drop;

	UPROPERTY(EditAnywhere, Category = "Cup")
	float cupSizeOrigin = 8.0f;

	UPROPERTY(EditAnywhere, Category = "Cup")
	float cupSize;
	
	UPROPERTY(EditAnywhere, Category = "Cup")
	float contents;
	
	UPROPERTY(VisibleAnywhere, Category = "Cup")
	int overlappedNum;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<FString> OrderArray;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<float> ContentsArray;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<int> GinArray;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float ginInside;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<int> LimeArray;
	
	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float limeInside;

	UPROPERTY(EditAnywhere, Category = "Cup")
	int iceCount = 0;
	
	class AIceCube* ice;

	float insideContents;

	UFUNCTION()
	virtual void LiquorScale();
};
