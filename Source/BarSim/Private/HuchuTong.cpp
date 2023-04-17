// Fill out your copyright notice in the Description page of Project Settings.


#include "HuchuTong.h"

#include "BarPlayer.h"
#include "IceCube.h"
#include "Components/BoxComponent.h"

// Sets default values
AHuchuTong::AHuchuTong()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("baseMesh"));
	//SetRootComponent(baseMesh);

	tongLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tongLeft"));
	tongLeft->SetupAttachment(RootComponent);

	tongRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tongRight"));
	tongRight->SetupAttachment(tongLeft, TEXT("TongSocket"));

	tongLeft->SetSimulatePhysics(true);
	tongRight->SetSimulatePhysics(false);
	
}

// Called when the game starts or when spawned
void AHuchuTong::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHuchuTong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHuchuTong::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	actorScale = SweepResult.GetActor()->GetActorScale3D();
	compScale = SweepResult.GetComponent()->GetComponentScale();
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	auto iceActor = Cast<AIceCube>(OtherActor);
	auto attachedComponent = SweepResult.GetComponent();
	auto attachedActor = SweepResult.GetActor();
	if(iceActor!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabb Ice"))
		iceActor->K2_AttachToComponent(tongRight, TEXT("TongAttach"),EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,EAttachmentRule::KeepWorld,false);
	}


}


