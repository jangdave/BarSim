// Fill out your copyright notice in the Description page of Project Settings.


#include "DropBase.h"

#include "CupBase.h"
#include "Components/SphereComponent.h"

// Sets default values
ADropBase::ADropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	sphereComp->SetSphereRadius(0.4f);
	SetRootComponent(sphereComp);
	sphereComp->SetSimulatePhysics(true);
	sphereComp->SetCollisionProfileName(FName("Fluid"));
}

// Called when the game starts or when spawned
void ADropBase::BeginPlay()
{
	Super::BeginPlay();

	//FTimerHandle timer;
	//GetWorldTimerManager().SetTimer(timer, this, &ADropBase::DropDestroy, 5.0f, false);
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADropBase::OnOverlap);
}

// Called every frame
void ADropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADropBase::DropDestroy()
{
	Destroy();
}

void ADropBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	cup = Cast<ACupBase>(OtherActor);
	if(cup)
	{
		if(cup->measureComp != OtherComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("drop Destroy"));
			Destroy();
		}
	}
}

