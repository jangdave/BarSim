// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GripMotionControllerComponent.h"



APlayerCharacter::APlayerCharacter()
{


	
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input 
	auto PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		// LocalPlayer
		auto localPlayer = PC->GetLocalPlayer();
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (subSystem)
		{			
			subSystem->AddMappingContext(IMC_Hand, 0);
		}
	}

	//RightMotionController->GetAllGrips();

	
}



void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


		//UE_LOG(LogTemp, Warning, TEXT("%f"), fingerPressedActionValue)
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
