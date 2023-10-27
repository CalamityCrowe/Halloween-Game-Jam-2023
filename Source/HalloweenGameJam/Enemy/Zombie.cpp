// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"

AZombie::AZombie()
{
	LoadEnemyData(EenemyType::Zombie); 
}

void AZombie::BeginPlay()
{
	Super::BeginPlay();
}

void AZombie::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
