// Fill out your copyright notice in the Description page of Project Settings.


#include "BarGameModeBase.h"
#include "Chair.h"
#include "EngineUtils.h"

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

	if(amountOfGin > 0)
	{
		CheckGin(cocName);
	}
	else if(amountOfRum > 0)
	{
		CheckRum(cocName);
	}
	else if(amountOfWhisky > 0)
	{
		CheckWhisky(cocName);
	}
	else
	{
		SomethingElse();
	}
}

void ABarGameModeBase::CheckGin(TArray<FString> cocName)
{
	// 진라임 판정
	if(amountOfLime > 0 && amountOfVermouth <= 0)
	{
		if(cocName.Num() == GinLime.Num())
		{
			for(int i = 0; i<cocName.Num(); i++)
			{
				for(int n = 0; n<GinLime.Num(); n++)
				{
					if(cocName[i] == GinLime[n] && i == n)
					{
						procedureScore -= 0;
					}
					else if(cocName[i] == GinLime[n] && i != n)
					{
						procedureScore -= 5;
					}
				}
			}
		}
		else
		{
			procedureScore -= 20;
		}
			
		CheckGinLime();
	}
	// 마티니 판정
	else if(amountOfVermouth > 0 && amountOfLime <= 0)
	{
		if(cocName.Num() == Martini.Num())
		{
			for(int i = 0; i<cocName.Num(); i++)
			{
				for(int n = 0; n<Martini.Num(); n++)
				{
					if(cocName[i] == Martini[n] && i == n)
					{
						procedureScore -= 0;
					}
					else if(cocName[i] == Martini[n] && i != n)
					{
						procedureScore -= 5;
					}
				}
			}
		}
		else
		{
			procedureScore -= 20;
		}
		
		CheckMartini();
	}
	// 레시피 범위 밖
	else
	{
		SomethingElse();
	}
	
}

void ABarGameModeBase::CheckWhisky(TArray<FString> cocName)
{
	if(amountOfVermouth > 0 && amountOfCampari > 0)
	{
		if(cocName.Num() == OldPal.Num())
		{
			for(int i = 0; i<cocName.Num(); i++)
			{
				for(int n = 0; n<OldPal.Num(); n++)
				{
					if(cocName[i] == OldPal[n] && i == n)
					{
						procedureScore -= 0;
					}
					else if(cocName[i] == OldPal[n] && i != n)
					{
						procedureScore -= 5;
					}
				}
			}
		}
		else
		{
			procedureScore -= 20;
		}
		
		CheckOldPal();
	}
	else
	{
		SomethingElse();
	}
}

void ABarGameModeBase::CheckRum(TArray<FString> cocName)
{
	if(amountOfLime > 0)
	{
		if(cocName.Num() == Daiquiri.Num())
		{
			for(int i = 0; i<cocName.Num(); i++)
			{
				for(int n = 0; n<Daiquiri.Num(); n++)
				{
					if(cocName[i] == Daiquiri[n] && i == n)
					{
						procedureScore -= 0;
					}
					else if(cocName[i] == Daiquiri[n] && i != n)
					{
						procedureScore -= 5;
					}
				}
			}
		}
		else
		{
			procedureScore -= 20;
		}
		
		CheckDaiquiri();
	}
	else
	{
		SomethingElse();
	}
}

void ABarGameModeBase::CheckGinLime()
{
	float ginLime = amountOfLime + amountOfGin;

	float ginRatio = amountOfGin/ginLime;

	float limeRatio = amountOfLime/ginLime;
	
	if(ginRatio > 0.71 && ginRatio < 0.79)
	{
		ratioScore -= 0;
	}
	else if(ginRatio > 0.6 && ginRatio <= 0.71)
	{
		ratioScore -= 10;
	}
	else if(ginRatio < 0.9 && ginRatio >= 0.79)
	{
		ratioScore -= 10;
	}
	else
	{
		ratioScore -= 30;
	}

	if(limeRatio > 0.23 && limeRatio < 0.27)
	{
		ratioScore -= 0;
	}
	else if(limeRatio > 0.2 && limeRatio <= 0.23)
	{
		ratioScore -= 10;
	}
	else if(limeRatio < 0.3 && limeRatio >= 0.27)
	{
		ratioScore -= 10;
	}
	else
	{
		ratioScore -= 30;
	}

	if(ginLime > 1.9 && ginLime < 2.1)
	{
		amountScore -= 0;
	}
	else if(ginLime > 1.8 && ginLime <= 1.9)
	{
		amountScore -= 5;
	}
	else if(ginLime < 2.2 && ginLime >= 2.1)
	{
		amountScore -= 5;
	}
	else
	{
		amountScore -= 10;
	}

	for(TActorIterator<AChair> it(GetWorld()); it; ++it)
	{
		if(it->bCheckCoctail != false)
		{
			it->ViewScore(procedureScore, ratioScore, amountScore);
		}
	}
}

void ABarGameModeBase::CheckMartini()
{
	float martini = amountOfVermouth + amountOfGin;

	float ginRatio = amountOfGin/martini;

	float vermouthRatio = amountOfVermouth/martini;
	
	if(ginRatio > 0.82 && ginRatio < 0.9)
	{
		ratioScore -= 0;
	}
	else if(ginRatio > 0.77 && ginRatio <= 0.82)
	{
		ratioScore -= 10;
	}
	else if(ginRatio < 0.95 && ginRatio >= 0.9)
	{
		ratioScore -= 10;
	}
	else
	{
		ratioScore -= 30;
	}

	if(vermouthRatio > 0.13 && vermouthRatio < 0.15)
	{
		ratioScore -= 0;
	}
	else if(vermouthRatio > 0.12 && vermouthRatio <= 0.13)
	{
		ratioScore -= 10;
	}
	else if(vermouthRatio < 0.16 && vermouthRatio >= 0.15)
	{
		ratioScore -= 10;
	}
	else
	{
		ratioScore -= 30;
	}

	if(martini > 2.1 && martini < 2.6)
	{
		amountScore -= 0;
	}
	else if(martini > 2.0 && martini <= 2.1)
	{
		amountScore -= 5;
	}
	else if(martini < 2.7 && martini >= 2.6)
	{
		amountScore -= 5;
	}
	else
	{
		amountScore -= 10;
	}

	for(TActorIterator<AChair> it(GetWorld()); it; ++it)
	{
		if(it->bCheckCoctail != false)
		{
			it->ViewScore(procedureScore, ratioScore, amountScore);
		}
	}
}

void ABarGameModeBase::CheckOldPal()
{
	float oldPal = amountOfCampari + amountOfVermouth + amountOfWhisky;

	float whiskyRatio = amountOfWhisky/oldPal;

	float vermouthRatio = amountOfVermouth/oldPal;

	float campariRatio = amountOfCampari/oldPal;
	
	if(whiskyRatio > 0.31 && whiskyRatio < 0.35)
	{
		ratioScore -= 0;
	}
	else if(whiskyRatio > 0.3 && whiskyRatio <= 0.31)
	{
		ratioScore -= 5;
	}
	else if(whiskyRatio < 0.36 && whiskyRatio >= 0.35)
	{
		ratioScore -= 5;
	}
	else
	{
		ratioScore -= 20;
	}

	if(vermouthRatio > 0.31 && vermouthRatio < 0.35)
	{
		ratioScore -= 0;
	}
	else if(vermouthRatio > 0.3 && vermouthRatio <= 0.31)
	{
		ratioScore -= 5;
	}
	else if(vermouthRatio < 0.36 && vermouthRatio >= 0.35)
	{
		ratioScore -= 5;
	}
	else
	{
		ratioScore -= 20;
	}

	if(campariRatio > 0.31 && campariRatio < 0.35)
	{
		ratioScore -= 0;
	}
	else if(campariRatio > 0.3 && campariRatio <= 0.31)
	{
		ratioScore -= 5;
	}
	else if(campariRatio < 0.36 && campariRatio >= 0.35)
	{
		ratioScore -= 5;
	}
	else
	{
		ratioScore -= 20;
	}

	if(oldPal > 2.85 && oldPal < 3.15)
	{
		amountScore -= 0;
	}
	else if(oldPal > 2.7 && oldPal <= 2.85)
	{
		amountScore -= 5;
	}
	else if(oldPal < 3.3 && oldPal >= 3.15)
	{
		amountScore -= 5;
	}
	else
	{
		amountScore -= 10;
	}

	for(TActorIterator<AChair> it(GetWorld()); it; ++it)
	{
		if(it->bCheckCoctail != false)
		{
			it->ViewScore(procedureScore, ratioScore, amountScore);
		}
	}
}

void ABarGameModeBase::CheckDaiquiri()
{
	float daiquiri = amountOfLime + amountOfRum;

	float rumRatio = amountOfRum/daiquiri;

	float limeRatio = amountOfLime/daiquiri;
	
	if(rumRatio > 0.71 && rumRatio < 0.79)
	{
		ratioScore -= 0;
	}
	else if(rumRatio > 0.67 && rumRatio <= 0.71)
	{
		ratioScore -= 10;
	}
	else if(rumRatio < 0.82 && rumRatio >= 0.79)
	{
		ratioScore -= 10;
	}
	else
	{
		ratioScore -= 30;
	}

	if(limeRatio > 0.23 && limeRatio < 0.27)
	{
		ratioScore -= 0;
	}
	else if(limeRatio > 0.22 && limeRatio <= 0.23)
	{
		ratioScore -= 10;
	}
	else if(limeRatio < 0.28 && limeRatio >= 0.27)
	{
		ratioScore -= 10;
	}
	else
	{
		ratioScore -= 30;
	}

	if(daiquiri > 2.5 && daiquiri < 2.8)
	{
		amountScore -= 0;
	}
	else if(daiquiri > 2.4 && daiquiri <= 2.5)
	{
		amountScore -= 5;
	}
	else if(daiquiri < 3.0 && daiquiri >= 2.8)
	{
		amountScore -= 5;
	}
	else
	{
		amountScore -= 10;
	}

	for(TActorIterator<AChair> it(GetWorld()); it; ++it)
	{
		if(it->bCheckCoctail != false)
		{
			it->ViewScore(procedureScore, ratioScore, amountScore);
		}
	}
}

void ABarGameModeBase::SomethingElse()
{
	procedureScore = 0;

	ratioScore = 0;

	amountScore = 0;
	
	for(TActorIterator<AChair> it(GetWorld()); it; ++it)
	{
		if(it->bCheckCoctail != false)
		{
			it->ViewScore(procedureScore, ratioScore, amountScore);
		}
	}
}
