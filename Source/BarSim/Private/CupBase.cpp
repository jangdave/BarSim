// Fill out your copyright notice in the Description page of Project Settings.


#include "CupBase.h"

#include "DropBase.h"

// Sets default values
ACupBase::ACupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cupComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cup"));
	SetRootComponent(cupComp);

	liquorComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquor"));
	liquorComp->SetupAttachment(cupComp);
	
	measureComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Measure"));
	measureComp->SetupAttachment(cupComp);
	
}

// Called when the game starts or when spawned
void ACupBase::BeginPlay()
{
	Super::BeginPlay();

	liquorComp->SetVisibility(false);
	measureComp->OnComponentBeginOverlap.AddDynamic(this, &ACupBase::AddLiquor);
}

// Called every frame
void ACupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACupBase::AddLiquor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	drop = Cast<ADropBase>(OtherActor);

	if(drop)
	{
		contents = contents + drop->dropMass;
		float insideContents = FMath::Clamp(contents, 0, cupSize);
		liquorComp->SetVisibility(true);
		liquorComp->SetRelativeScale3D(FVector(1,1,insideContents / cupSize));
		UE_LOG(LogTemp, Warning, TEXT("%f"), insideContents);
		drop->Destroy();
	}
}

