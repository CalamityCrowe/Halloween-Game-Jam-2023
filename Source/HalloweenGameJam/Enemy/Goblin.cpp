// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"

AGoblin::AGoblin()
{
	LoadEnemyData(EenemyType::Goblin);
}

void AGoblin::BeginPlay()
{
	Super::BeginPlay();
}

void AGoblin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
