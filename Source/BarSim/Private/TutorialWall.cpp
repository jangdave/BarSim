// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWall.h"
#include "Components/BoxComponent.h"

// Sets default values
ATutorialWall::ATutorialWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(650.0f, 20.0f, 100.0f));
	boxComp->SetCollisionResponseToAllChannels(ECR_Block);
}

// Called when the game starts or when spawned
void ATutorialWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATutorialWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorialWall::OpenCollision()
{
	boxComp->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ATutorialWall::CloseCollision()
{
	boxComp->SetCollisionResponseToAllChannels(ECR_Block);
}