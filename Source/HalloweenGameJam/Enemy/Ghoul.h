// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Enemy.h"
#include "Ghoul.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENGAMEJAM_API AGhoul : public ABase_Enemy
{
	GENERATED_BODY()
public:
	AGhoul(); 

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
};
