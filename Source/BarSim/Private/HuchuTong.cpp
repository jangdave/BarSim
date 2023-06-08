// Fill out your copyright notice in the Description page of Project Settings.


#include "HuchuTong.h"

#include "BarPlayer.h"
#include "IceCube.h"
#include "Components/BoxComponent.h"

// Sets default values
AHuchuTong::AHuchuTong(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
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


void AHuchuTong::SetSimulateAndTickDisable()
{
	GetWorldTimerManager().SetTimer(simHandle,this, &AHuchuTong::SimulateAndTickDisable, 10.0f, false);	
}

void AHuchuTong::SimulateAndTickDisable()
{
		this->DisableComponentsSimulatePhysics();
		this->SetActorTickEnabled(false);
		//UE_LOG(LogTemp, Warning, TEXT("SetSimulateAndTickDisalbe"))
}

