// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLight.h"

#include "Components/SpotLightComponent.h"

// Sets default values
ATutorialLight::ATutorialLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));	
	SetRootComponent(spotLight);
	spotLight->SetAttenuationRadius(3000.0f);
	spotLight->SetIntensity(lightIntensity);
	spotLight->SetIntensityUnits(ELightUnits::Candelas);
	spotLight->SetOuterConeAngle(30.0f);
	spotLight->SetRelativeRotation(FRotator(-90.0f, 0, 0));
	
}

// Called when the game starts or when spawned
void ATutorialLight::BeginPlay()
{
	Super::BeginPlay();
	lightIntensity = 300.0f;
	spotLight->SetIntensity(lightIntensity);
	spotLight->SetRelativeRotation(FRotator(-90.0f, 0, 0));
}

// Called every frame
void ATutorialLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

