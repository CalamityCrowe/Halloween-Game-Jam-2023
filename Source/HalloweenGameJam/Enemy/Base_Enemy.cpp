// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Enemy.h"

// Sets default values
ABase_Enemy::ABase_Enemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_Enemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABase_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EnemyType = EenemyType::None;

}

// Called to bind functionality to input
void ABase_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABase_Enemy::LoadEnemyData(EenemyType newEnemyType)
{
	auto DataTable = ConstructorHelpers::FObjectFinder<UDataTable>(TEXT("DataTable'/Game/DataTables/EnemyData.EnemyData'"));
	EnemyData = DataTable.Object;
	if (EnemyData)
	{
		FindEnemyTypeFromData(newEnemyType);
	}
}

void ABase_Enemy::FindEnemyTypeFromData(EenemyType newEnemyType)
{
	EenemyType FindThisType = newEnemyType;

	FEnemyData* FoundRow = nullptr;

	for (auto It : EnemyData->GetRowMap())
	{
		if (FEnemyData* Row = reinterpret_cast<FEnemyData*>(It.Value))
		{
			if (Row->ObjectType == FindThisType)
			{
				FoundRow = Row;
				break;
			}
		}
	}
	if (FoundRow)
	{
		EnemyType = FoundRow->ObjectType;
		GetMesh()->SetSkeletalMesh(FoundRow->ObjectMesh);
		SetActorScale3D(FoundRow->ObjectScale);
	}
}

