// Fill out your copyright notice in the Description page of Project Settings.


#include "Lich.h"

ALich::ALich()
{
	LoadEnemyData(EenemyType::Lich); 
}

void ALich::BeginPlay()
{
	Super::BeginPlay();
}

void ALich::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
