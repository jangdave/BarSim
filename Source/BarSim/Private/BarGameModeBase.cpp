// Fill out your copyright notice in the Description page of Project Settings.


#include "BarGameModeBase.h"
#include "Chair.h"
#include "EngineUtils.h"
#include "SpawnManager.h"
#include "Kismet/GameplayStatics.h"

ABarGameModeBase::ABarGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABarGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void ABarGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ABarGameModeBase::GetCup(TArray<FString> cocName, TArray<float> cocliter)
{
	for(int i = 0; i<cocName.Num(); i++)
	{
		if(cocName[i] == "Whisky")
		{
			amountOfWhisky += cocliter[i];
		}
		else if(cocName[i] == "Rum")
		{
			amountOfRum += cocliter[i];
		}
		else if(cocName[i] == "Gin")
		{
			amountOfGin += cocliter[i];
		}
		else if(cocName[i] == "Vermouth")
		{
			amountOfVermouth += cocliter[i];
		}
		else if(cocName[i] == "Lime")
		{
			amountOfLime += cocliter[i];
		}
		else if(cocName[i] == "Campari")
		{
			amountOfCampari += cocliter[i];
		}
	}
	
	CheckGin();

	CheckRum();

	CheckWhisky();
}

void ABarGameModeBase::CheckGin()
{
	if(amountOfGin > 0)
	{
		if(amountOfLime > 0)
		{
			CheckGinLime();
		}
		else if(amountOfVermouth > 0)
		{
			CheckMartini();
		}
		else
		{
			
		}
	}
}

void ABarGameModeBase::CheckWhisky()
{
	if(amountOfWhisky > 0)
	{
		if(amountOfVermouth > 0 && amountOfCampari > 0)
		{
			CheckOldPal();
		}
		else
		{
			
		}
	}
}

void ABarGameModeBase::CheckRum()
{
	if(amountOfRum > 0)
	{
		if(amountOfLime > 0)
		{
			CheckDaiquiri();
		}
		else
		{
			
		}
	}
}

void ABarGameModeBase::CheckGinLime()
{
	float ginLime = amountOfLime + amountOfGin;

	float limeRatio = amountOfLime/ginLime;

	float ginRatio = amountOfGin/ginLime;
	
	if(ginRatio == 0.75)
	{
		
	}
	else if(ginRatio > 0.72 && ginRatio < 0.75)
	{
		totalScore -= 5;
	}
	else if(ginRatio < 0.79 && ginRatio > 0.75)
	{
		totalScore -= 5;
	}
	else
	{
		totalScore -= 30;
	}

	if(limeRatio == 0.25)
	{
		
	}
	else if(limeRatio > 0.23 && limeRatio < 0.25)
	{
		totalScore -= 5;
	}
	else if(limeRatio < 0.27 && limeRatio > 0.25)
	{
		totalScore -= 5;
	}
	else
	{
		totalScore -= 30;
	}

	if(ginLime == 2)
	{
		
	}
	else if(ginLime > 1.9 && ginLime < 2)
	{
		totalScore -= 5;
	}
	else if(ginLime < 2.1 && ginLime > 2)
	{
		totalScore -= 5;
	}
	else
	{
		totalScore -= 30;
	}

	for(TActorIterator<AChair> it(GetWorld()); it; ++it)
	{
		if(it->bCheckCoctail != false)
		{
			it->ViewScore(totalScore);
		}
	}
}

void ABarGameModeBase::CheckMartini()
{
	
}

void ABarGameModeBase::CheckOldPal()
{
	
}

void ABarGameModeBase::CheckDaiquiri()
{
	
}

void ABarGameModeBase::SomethingElse()
{
	
}
