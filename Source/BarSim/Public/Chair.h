// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.generated.h"

UCLASS()
class BARSIM_API AChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category=ChairSetting)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category=ChairSetting)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	bool bCheck;

	UPROPERTY(EditAnywhere)
	bool bCheckCoctail;

	UPROPERTY(EditAnywhere)
	bool bCheckCoaster;
	
	UPROPERTY(EditAnywhere)
	bool bCheckPlayer;
	
	UPROPERTY(EditAnywhere, Category=CocktailZone)
	class UBoxComponent* coctailBoxComp;

	UPROPERTY(EditAnywhere, Category=PlayerZone)
	class UBoxComponent* playerBoxComp;

	UFUNCTION()
	void OnCupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void EndCupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void EndPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
