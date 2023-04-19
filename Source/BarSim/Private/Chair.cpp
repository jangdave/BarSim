// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"
#include "Components/BoxComponent.h"

// Sets default values
AChair::AChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);

	coctailBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("coctailBoxComp"));
	coctailBoxComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	coctailBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AChair::OnOverlap);
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChair::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

