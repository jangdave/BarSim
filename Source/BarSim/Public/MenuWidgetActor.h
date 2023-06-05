// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MenuWidgetActor.generated.h"

UCLASS()
class BARSIM_API AMenuWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMenuWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;
	
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* menuWidget;
	
	UPROPERTY()
	class UBarGameInstance* gi;

	UPROPERTY()
	class UMenuWidget* menu_UI;

	UPROPERTY()
	class APlayerCharacter* player;
	
	UFUNCTION()
	void Destroy();

	UFUNCTION()
	void SetMenu();
};
