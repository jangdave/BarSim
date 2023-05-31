// Fill out your copyright notice in the Description page of Project Settings.


#include "OliveVat.h"

// Sets default values
AOliveVat::AOliveVat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	oliveVatComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("oliveVatComp"));
	SetRootComponent(oliveVatComp);
}

// Called when the game starts or when spawned
void AOliveVat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOliveVat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

