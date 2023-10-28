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
	GEngine->AddOnScreenDebugMessage(12, 2, FColor::Yellow, TEXT("Possessddddddddddddddddddded"));


	if (time >= 2)
	{
		if (ABase_Enemy* en = Cast<ABase_Enemy>(GetPawn()))
		{
			MoveActor(FVector(en->GetPlayer()->GetActorLocation()));
			time = 0; 
		}
	}

}

void ABase_Enemy_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, TEXT("Possessed"));
	}
}

void ABase_Enemy_Controller::MoveActor(FVector newDir)
{

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (APawn* ControlledPawn = GetPawn())
	{
		if (ABase_Enemy* CurrentEnemy = Cast<ABase_Enemy>(ControlledPawn))
		{
			FNavLocation newLocation;
			if (NavArea->GetRandomPointInNavigableRadius(newDir, 50, newLocation))
			{
				MoveToLocation(newLocation.Location);
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("AAAAAAAAAAAAA"));
			}
		}

	}
}
