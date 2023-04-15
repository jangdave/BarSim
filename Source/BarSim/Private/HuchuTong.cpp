// Fill out your copyright notice in the Description page of Project Settings.


#include "HuchuTong.h"

#include "BarPlayer.h"

// Sets default values
AHuchuTong::AHuchuTong()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("baseMesh"));
	SetRootComponent(baseMesh);

	tongLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tongLeft"));
	tongLeft->SetupAttachment(baseMesh);

	tongRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tongRight"));
	tongRight->SetupAttachment(tongLeft, TEXT("TongSocket"));

	tongLeft->SetSimulatePhysics(true);
	tongRight->SetSimulatePhysics(false);

	
}

// Called when the game starts or when spawned
void AHuchuTong::BeginPlay()
{
	Super::BeginPlay();


	player = Cast<ABarPlayer>(GetAttachParentActor());
	
}

// Called every frame
void AHuchuTong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

