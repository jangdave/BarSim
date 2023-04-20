// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tablet.generated.h"

UCLASS()
class BARSIM_API ATablet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATablet();


	UPROPERTY(EditAnywhere, Category=tabletSettings)
	class UStaticMeshComponent* tabletMesh;

	UPROPERTY(EditAnywhere, Category=tabletSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=tabletSettings)
	class UWidgetComponent* widgetComp;



class ABarPlayer* player;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
