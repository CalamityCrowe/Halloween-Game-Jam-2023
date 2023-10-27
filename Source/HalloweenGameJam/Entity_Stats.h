// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity_Stats.generated.h"

USTRUCT(BlueprintType)
struct HALLOWEENGAMEJAM_API FEntity_Stats
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDead;

	// Sets default values for this actor's properties
	FEntity_Stats() : Health(NULL), bIsDead(NULL)
	{

	}


};
