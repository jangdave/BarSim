// Fill out your copyright notice in the Description page of Project Settings.


#include "BarMat.h"

#include "CupBase.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Components/BoxComponent.h"

// Sets default values
ABarMat::ABarMat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	niagara->SetupAttachment(boxComp);
	
}

// Called when the game starts or when spawned
void ABarMat::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABarMat::OnMat);
}

// Called every frame
void ABarMat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarMat::OnMat(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	cup = Cast<ACupBase>(OtherActor);

	if(cup)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("barmat overlapped"));
		cup->cupComp->SetSimulatePhysics(false);
	}
}

