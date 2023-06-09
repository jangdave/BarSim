// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfSlicedLimeVat.h"

// Sets default values
AHalfSlicedLimeVat::AHalfSlicedLimeVat(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
	
}

// Called when the game starts or when spawned
void AHalfSlicedLimeVat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHalfSlicedLimeVat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHalfSlicedLimeVat::SetSimulateAndTickDisable()
{
	GetWorldTimerManager().SetTimer(simHandle,this, &AHalfSlicedLimeVat::SimulateAndTickDisable, 10.0f, false);	
}

void AHalfSlicedLimeVat::SimulateAndTickDisable()
{
	if(meshComp)
	{
		this->DisableComponentsSimulatePhysics();
		meshComp->SetSimulatePhysics(false);
		this->SetActorTickEnabled(false);
		//UE_LOG(LogTemp, Warning, TEXT("SetSimulateAndTickDisalbe"))
	}
}