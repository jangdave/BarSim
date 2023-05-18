// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grippables/GrippableActor.h"
#include "CupBase.generated.h"

UCLASS()
class BARSIM_API ACupBase : public AGrippableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACupBase(const FObjectInitializer& ObjectInitializer);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cup")
	class UWidgetComponent* widgetComp;

	UFUNCTION()
	void AddLiquor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void ExtractIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Cup")
	class ADropBase* drop;

	UPROPERTY(EditAnywhere, Category = "Cup")
	class AMixedDrop* mixedDropOverlapped;

	UPROPERTY(EditAnywhere, Category = "Cup")
	float cupSizeOrigin = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cup")
	float cupSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cup")
	float contents;
	
	UPROPERTY(VisibleAnywhere, Category = "Cup")
	int overlappedNum;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<FString> NameArray;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<float> ContentsArray;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<bool> MixArray;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float ginInside;
	
	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float limeInside;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float rumInside;
	
	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float sugarInside;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float vermouthInside;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float campariInside;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float whiskeyInside;

	UPROPERTY(EditAnywhere, Category = "Cup")
	int iceCount = 0;

	UPROPERTY(EditAnywhere, Category = "Cup")
	class AIceCube* ice;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	float insideContents;

	UFUNCTION()
	virtual void LiquorScale();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cup")
	bool bStirStarted;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cup")
	float stirRate;

	//스터해야하는 횟수, 에디터 수정 가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cup")
	float stirNeeded = 3;
	
	UPROPERTY(VisibleAnywhere, Category ="Cup")
	float allInside;

	UPROPERTY(EditAnywhere, Category = "Cup")
	bool bStirred;

	UPROPERTY(EditAnywhere, Category = "Cup")
	bool bStirredLater;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cup")
	float timePassed;

	//shake array에 shake 방울 담기
	UPROPERTY(VisibleAnywhere, Category = "Cup")
	TArray<bool> ShakeArray;

	UPROPERTY(EditAnywhere, Category = "Cup")
	bool bShaked;

	UPROPERTY(BlueprintReadWrite, Category = "Cup")
	class APlayerCharacter* player;

	UPROPERTY()
	class UCupWidget* cupWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cup")
	TArray<FString> widgetNameArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cup")
	TArray<float> widgetContentsArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cup")
	float widgetTime;

	UPROPERTY(VisibleAnywhere, Category = "Cup")
	bool bWidgetOn;

	UPROPERTY(VisibleAnywhere, Category	= "Cup")
	bool bWidgetAnimOn;

	UFUNCTION()
	void SetCupEmpty();

	UPROPERTY()
	class ASteelSink* steelSink;

	UPROPERTY()
	bool isSteelSinkCasted=false;

	int32 sinkArrayNum=0;

	UPROPERTY()
	bool isCupTickActivated = false;

	UFUNCTION()
	virtual void CupStop();
};
