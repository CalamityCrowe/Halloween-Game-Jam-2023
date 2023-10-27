// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Enemy_Controller.h"
#include "NavigationSystem.h"

ABase_Enemy_Controller::ABase_Enemy_Controller()
{
}
void ABase_Enemy_Controller::BeginPlay() 
{
	Super::BeginPlay(); 
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this); 
}
void ABase_Enemy_Controller::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime); 
}

void ABase_Enemy_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}
