// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Enemy.h"
#include "Lich.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENGAMEJAM_API ALich : public ABase_Enemy
{
	GENERATED_BODY()
public:
	ALich();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
