// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghoul.h"

AGhoul::AGhoul()
{
	LoadEnemyData(EenemyType::Ghoul); 
}

void AGhoul::BeginPlay()
{
	Super::BeginPlay();
}

void AGhoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
