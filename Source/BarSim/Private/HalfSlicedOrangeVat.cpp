// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfSlicedOrangeVat.h"

// Sets default values
AHalfSlicedOrangeVat::AHalfSlicedOrangeVat(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void AHalfSlicedOrangeVat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHalfSlicedOrangeVat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHalfSlicedOrangeVat::SetSimulateAndTickDisable()
{
	GetWorldTimerManager().SetTimer(simHandle,this, &AHalfSlicedOrangeVat::SimulateAndTickDisable, 10.0f, false);	
}

void AHalfSlicedOrangeVat::SimulateAndTickDisable()
{
	if(meshComp)
	{
		this->DisableComponentsSimulatePhysics();
		meshComp->SetSimulatePhysics(false);
		this->SetActorTickEnabled(false);
		//UE_LOG(LogTemp, Warning, TEXT("SetSimulateAndTickDisalbe"))
	}
}
