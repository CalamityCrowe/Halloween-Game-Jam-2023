// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Base_Enemy_Controller.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENGAMEJAM_API ABase_Enemy_Controller : public AAIController
{
	GENERATED_BODY()
public:
	ABase_Enemy_Controller();
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float) override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	class UNavigationSystemV1* NavArea; 

};
