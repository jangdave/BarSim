// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BARSIM_API APlayerCharacter : public AVRCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	double fingerPressedActionValue;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Hand;
	
UFUNCTION(BlueprintCallable)
	void CheckGrabbedObjectRight();
	UFUNCTION(BlueprintCallable)
	void CheckGrabbedObjectLeft();


	// 오른손 그랩 액터
	UPROPERTY()
	class AActor* GrabbedActorRight;

	// HuchuTong Ref
	UPROPERTY()
	class AHuchuTong* huchuTong;
};
