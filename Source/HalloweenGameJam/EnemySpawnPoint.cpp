// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "Enemy/Base_Enemy.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemySpawn = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Spawn"));
	RootComponent = EnemySpawn;
	SpawnDirection = CreateOptionalDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	SpawnDirection->ArrowColor = FColor::Red;
	SpawnDirection->SetupAttachment(EnemySpawn);

	LoadEnemyPrefabDataTable();

}

// Called when  the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	LoadEnemyPrefab(EnemyType);

	const FActorSpawnParameters SpawnParameters;

	if (ABase_Enemy* newEnemy = GetWorld()->SpawnActor<ABase_Enemy>(EnemyReference, GetActorLocation(), GetActorRotation(), SpawnParameters))
	{


	}

}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawnPoint::LoadEnemyPrefabDataTable()
{
	auto DataTable = ConstructorHelpers::FObjectFinder<UDataTable>(TEXT("DataTable'/Game/DataTables/DT_EnemyPrefabData.DT_EnemyPrefabData'"));
	EnemyData = DataTable.Object;

}

void AEnemySpawnPoint::LoadEnemyPrefab(EenemyType newEnemy)
{
	EenemyType FindThisType = newEnemy;

	FEnemyPrefabData* FoundRow = nullptr;

	for (auto It : EnemyData->GetRowMap())
	{
		if (FEnemyPrefabData* Row = reinterpret_cast<FEnemyPrefabData*>(It.Value))
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
		EnemyReference = FoundRow->ObjectPrefab;
		EnemyHealth = FoundRow->ObjectHealth;
	}
}

