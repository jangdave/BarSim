// Fill out your copyright notice in the Description page of Project Settings.


#include "MartiniCup.h"

void AMartiniCup::LiquorScale()
{
	liquorComp->SetRelativeScale3D(FVector(insideContents / cupSize));
}
