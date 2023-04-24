// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HuchuTong.generated.h"

UCLASS()
class BARSIM_API AHuchuTong : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHuchuTong();

UPROPERTY(EditAnywhere, Category=TongSettings)
	class UStaticMeshComponent* tongLeft;

	UPROPERTY(EditAnywhere, Category=TongSettings)
	class UStaticMeshComponent* tongRight;

	//UPROPERTY(EditAnywhere, Category=TongSettings)
	//class UBoxComponent* attachComp;

	UPROPERTY()
	FVector compScale;
	UPROPERTY()
	FVector actorScale;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
