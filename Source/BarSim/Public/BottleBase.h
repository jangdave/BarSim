// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BottleBase.generated.h"

UCLASS()
class BARSIM_API ABottleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABottleBase();

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

	UPROPERTY(EditAnywhere, Category = "Bottle")
	class UNiagaraComponent* stream;

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
};
