// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Enemy.h"
#include "Zombie.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENGAMEJAM_API AZombie : public ABase_Enemy
{
	GENERATED_BODY()
public:
	AZombie();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
};
