// Fill out your copyright notice in the Description page of Project Settings.


#include "Skeleton_Enemy.h"

ASkeleton_Enemy::ASkeleton_Enemy()
{
	LoadEnemyData(EenemyType::Skeleton); 
}

void ASkeleton_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void ASkeleton_Enemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
