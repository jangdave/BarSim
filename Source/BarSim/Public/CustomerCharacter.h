// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomerCharacter.generated.h"

UCLASS()
class BARSIM_API ACustomerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FSM)
	class UCustomerFSM* costomerFSM;

	UPROPERTY(EditAnywhere)
	class UCustomerAnimInstance* customerAnim;

	class ASpawnManager* spawnManager;
	
	// 스폰시 메쉬 설정 함수
	void SetMesh();
	
	int32 SetRandRange(int32 idxStart, int32 idxEnd);

	// 남성 메쉬
	TArray<ConstructorHelpers::FObjectFinder<USkeletalMesh>> manMesh;

	// 여성 메쉬
	TArray<ConstructorHelpers::FObjectFinder<USkeletalMesh>> womenMesh;
};
