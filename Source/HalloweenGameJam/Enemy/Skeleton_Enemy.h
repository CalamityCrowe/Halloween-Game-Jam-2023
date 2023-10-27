// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Enemy.h"
#include "Skeleton_Enemy.generated.h"

/**
 *
 */
UCLASS()
class HALLOWEENGAMEJAM_API ASkeleton_Enemy : public ABase_Enemy
{
	GENERATED_BODY()
public:
	ASkeleton_Enemy();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
