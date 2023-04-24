// Fill out your copyright notice in the Description page of Project Settings.


#include "BarFridge.h"

#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ABarFridge::ABarFridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	barFridgeMesh = CreateDefaultSubobject<UStaticMeshComponent>("barFridgeMesh");
	SetRootComponent(barFridgeMesh);
	barFridgeMesh->SetRelativeScale3D(FVector(0.6f));

	barFridgeDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("barFridgeDoorMesh");
	barFridgeDoorMesh->SetupAttachment(RootComponent);

	physicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("physicsConstraint");
	//physicsConstraint->SetupAttachment(RootComponent);

	//doorGrabComp=CreateDefaultSubobject<UBoxComponent>("doorGrabComp");
	//doorGrabComp->SetupAttachment(barFridgeDoorMesh);
	//doorGrabComp->SetRelativeLocation(FVector(92.2, 0, 1.7));
	//doorGrabComp->SetBoxExtent(FVector(8, 90, 130));
	
	
}

// Called when the game starts or when spawned
void ABarFridge::BeginPlay()
{
	Super::BeginPlay();

	//barFridgeDoorMesh->SetRelativeRotation(FRotator::ZeroRotator);
	barFridgeDoorMesh->SetSimulatePhysics(true);
	physicsConstraint->SetDisableCollision(true);
	//doorGrabComp->SetSimulatePhysics(true);
	
}

// Called every frame
void ABarFridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

