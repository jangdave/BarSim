// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"
#include "BarGameModeBase.h"
#include "BarPlayer.h"
#include "Coaster.h"
#include "CoctailScoreWidget.h"
#include "CupBase.h"
#include "Components/BoxComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"

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

	playerBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("playerBoxComp"));
	playerBoxComp->SetupAttachment(boxComp);

	coctailWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CoctailWidget"));
	coctailWidget->SetupAttachment(coctailBoxComp);
}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	coctailBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AChair::OnCupOverlap);
	coctailBoxComp->OnComponentEndOverlap.AddDynamic(this, &AChair::EndCupOverlap);

	playerBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AChair::OnPlayerOverlap);
	playerBoxComp->OnComponentEndOverlap.AddDynamic(this, &AChair::EndPlayerOverlap);

	score_UI = Cast<UCoctailScoreWidget>(coctailWidget->GetUserWidgetObject());
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChair::OnCupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto coaster = Cast<ACoaster>(OtherActor);
	auto coctail = Cast<ACupBase>(OtherActor);
	
	if(coctail != nullptr)
	{
		bCheckCoctail = true;

		auto gm = Cast<ABarGameModeBase>(GetWorld()->GetAuthGameMode());

		gm->GetCup(coctail->OrderArray, coctail->ContentsArray);
	}
	if(coaster != nullptr)
	{
		bCheckCoaster = true;
	}
}

void AChair::EndCupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	auto coctail = Cast<ACupBase>(OtherActor);
	auto coaster = Cast<ACoaster>(OtherActor);

	if(coctail != nullptr)
	{
		bCheckCoctail = false;
	}
	if(coaster != nullptr)
	{
		bCheckCoaster = false;	
	}
}

void AChair::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto target = Cast<ABarPlayer>(OtherActor);

	if(target != nullptr)
	{
		bCheckPlayer = true;
	}
}

void AChair::EndPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto target = Cast<ABarPlayer>(OtherActor);

	if(target != nullptr)
	{
		bCheckPlayer = false;
	}
}

void AChair::ViewScore(int32 score)
{
	score_UI->SetVisibility(ESlateVisibility::Visible);
	
	score_UI->text_Score->SetText(FText::AsNumber(score));
}

