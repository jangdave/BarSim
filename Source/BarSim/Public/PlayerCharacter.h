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

	// Widget Components
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UWidgetInteractionComponent* widgetInteractionComp;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UWidgetInteractionComponent* widgetInteractionCompLeft;

	// Aims
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HandComp")
	class UMotionControllerComponent* RightAim;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HandComp")
	class UMotionControllerComponent* LeftAim;

	// Inputs
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* VREInputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Hand;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* UseHeldObjectRight;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* UseHeldObjectLeft;


	// Functions
	UFUNCTION(BlueprintCallable)
	void CheckGrabbedObjectRight();
	UFUNCTION(BlueprintCallable)
	void CheckGrabbedObjectLeft();
	UFUNCTION(BlueprintCallable)
	void CheckDroppedObjectRight();
	UFUNCTION(BlueprintCallable)
	void CheckDroppedObjectLeft();
	void FireRight();
	void FireLeft();
	void FireReleasedRight();
	void FireReleasedLeft();

	// Grabbing Boolean
	bool IsGrabbedLeft = false;
	bool IsGrabbedRight = false;
	bool isGrabbingTongsLeft = false;
	bool isGrabbingTongsRight = false;
	bool isGrabbingWithTongsRight=false;
	bool isGrabbingWithTongsLeft=false;
	bool isTongsTickEnabled = true;
	bool isTongsTickEnabledL = true;
	bool isRecipeMode = false;
	bool isGrabbingBottleRight = false;
	bool isGrabbingBottleLeft = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isGrabbingTabletRight = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isGrabbingTabletLeft = false;
	bool isGrabbingCoasterRight=false;
	bool isGrabbingCoasterLeft = false;
	bool isGrabbingCupLeft = false;
	bool isGrabbingCupRight = false;
	bool isGrabbingBarSpoonLeft=false;
	bool isGrabbingBarSpoonRight=false;
	bool isGrabbingShakerRight=false;
	bool isGrabbingShakerLeft=false;
	bool isGrabbingShakerStrainerRight=false;
	bool isGrabbingShakerStrainerLeft=false;
	bool isGrabbingStrainerRight=false;
	bool isGrabbingStrainerLeft=false;
	bool isGrabbingMixingGlassRight=false;
	bool isGrabbingMixingGlassLeft=false;
	bool isGrabbingShakerLidRight=false;
	bool isGrabbingShakerLidLeft=false;
	bool isGrabbingIceWithTongsRight=false;
	bool isGrabbingIceWithTongsLeft=false;
	bool isGrabbingLimeWithTongsRight=false;
	bool isGrabbingLimeWithTongsLeft=false;
	
	
	UPROPERTY()
	FRotator initHandRot;
	UPROPERTY()
	FRotator initHandRotL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	double fingerPressedActionValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	double fingerPressedActionValueLeft;

	UPROPERTY(EditDefaultsOnly)
	float TongsGrabRange = 10;
	
	// 오른손 그랩 액터
	UPROPERTY()
	class AActor* GrabbedActorRight;
	// 왼손 그랩 액터
	UPROPERTY()
	class AActor* GrabbedActorLeft;

	// Tongs를 통한 그랩 오른쪽 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectWithTongsRight;
	UPROPERTY()
	class AActor* GrabbedActorWithTongsRight;
	// Tongs를 통한 그랩 왼쪽 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectWithTongsLeft;
	UPROPERTY()
	class AActor* GrabbedActorWithTongsLeft;

	// References
	UPROPERTY()
	class AHuchuTong* huchuTong;
	UPROPERTY()
	class AHuchuTong* huchuTongL;
	UPROPERTY()
	class ABottleBase* bottle;
	UPROPERTY()
	class ABottleBase* bottleL;
	UPROPERTY()
	class ATablet* tablet;
	UPROPERTY()
	class ATablet* tabletL;
	UPROPERTY()
	class ACoaster* coaster;
	UPROPERTY()
	class ACoaster* coasterL;
	UPROPERTY()
	class ACupBase* cup;
	UPROPERTY()
	class ACupBase* cupL;
	UPROPERTY()
	class AIceCube* iceCube;
	UPROPERTY()
	class AIceCube* iceCubeL;
	UPROPERTY()
	class ABarSpoon* barSpoon;
	UPROPERTY()
	class ABarSpoon* barSpoonL;
	UPROPERTY()
	class AShakerLid* shakerLid;
	UPROPERTY()
	class AShakerLid* shakerLidL;
	UPROPERTY()
	class AStrainer* strainer;
	UPROPERTY()
	class AStrainer* strainerL;
	UPROPERTY()
	class AShakerStrainer* shakerStrainer;
	UPROPERTY()
	class AShakerStrainer* shakerStrainerL;
	UPROPERTY()
	class AShaker* shaker;
	UPROPERTY()
	class AShaker* shakerL;
	UPROPERTY()
	class AMixingGlass* mixingGlass;
	UPROPERTY()
	class AMixingGlass* mixingGlassL;
	UPROPERTY()
	class ASlicedLime* slicedLime;
	UPROPERTY()
	class ASlicedLime* slicedLimeL;
	UPROPERTY()
	class AHalfSlicedLime* halfSlicedLime;
	UPROPERTY()
	class AHalfSlicedLime* halfSlicedLimeL;


	
};
