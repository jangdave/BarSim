// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartManager.h"
#include "BarGameInstance.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameStartManager::AGameStartManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
}

// Called when the game starts or when spawned
void AGameStartManager::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AGameStartManager::OnOverlap);

}

// Called every frame
void AGameStartManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGameStartManager::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerCharacter>(OtherActor);

	if(player != nullptr)
	{
		auto gi = Cast<UBarGameInstance>(GetGameInstance());
		
		gi->goToMainMapDele.Execute();

		if(gi->bCheckGameMode != false)
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName("BarMainMap"));
		}
		else
		{
			gi->bCheckGameMode = true;
			
			UGameplayStatics::OpenLevel(GetWorld(), FName("BarTutorialMap"));
		}
	}
}

