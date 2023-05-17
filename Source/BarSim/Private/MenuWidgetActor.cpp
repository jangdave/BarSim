// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidgetActor.h"

#include "BarGameInstance.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMenuWidgetActor::AMenuWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	
	menuWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("menuWidget"));
	menuWidget->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void AMenuWidgetActor::BeginPlay()
{
	Super::BeginPlay();

	auto gi = Cast<UBarGameInstance>(GetGameInstance());

	if(gi != nullptr)
	{
		if(gi->checkDayCount != 0)
		{
			Destroy();
		}
	}
}

// Called every frame
void AMenuWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMenuWidgetActor::Destroy()
{
	this->Destroyed();
}

