// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalCharacter.h"
#include "OldPalAnimInstance.h"
#include "OldPalFSM.h"
#include "Components/WidgetComponent.h"

// Sets default values
AOldPalCharacter::AOldPalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ConstructorHelpers::FClassFinder<UAnimInstance> tempAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Jang/ABP_OldPalAnim.ABP_OldPalAnim_C'"));
	//if(tempAnim.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(tempAnim.Class);
	//}
	
	oldPalFSM = CreateDefaultSubobject<UOldPalFSM>(TEXT("oldPalFSM"));

	oldPalWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("oldPalWidget"));
	oldPalWidget->SetupAttachment(GetMesh());
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AOldPalCharacter::BeginPlay()
{
	Super::BeginPlay();

	//oldPalAnim = Cast<UOldPalAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AOldPalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOldPalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

