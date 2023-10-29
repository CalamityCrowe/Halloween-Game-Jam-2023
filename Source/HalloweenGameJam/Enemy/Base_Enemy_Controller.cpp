// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Enemy_Controller.h"

#include "Base_Enemy.h"
#include "NavigationSystem.h"
#include "HalloweenGameJam/Player/Base_Player.h"

ABase_Enemy_Controller::ABase_Enemy_Controller()
{
	time = 0;
}
void ABase_Enemy_Controller::BeginPlay()
{
	Super::BeginPlay();
}
void ABase_Enemy_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time += DeltaTime;
	//GEngine->AddOnScreenDebugMessage(12, 2, FColor::Yellow, TEXT("Possessddddddddddddddddddded"));





}

void ABase_Enemy_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, TEXT("Possessed"));
	}
}

void ABase_Enemy_Controller::MoveActor(AActor* TargetActor)
{

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	if (APawn* ControlledPawn = GetPawn())
	{
		const ANavigationData* NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);

		if (ABase_Enemy* CurrentEnemy = Cast<ABase_Enemy>(ControlledPawn))
		{

			MoveToActor(TargetActor, 0); 

			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("AAAAAAAAAAAAA"));

		}

	}
}
