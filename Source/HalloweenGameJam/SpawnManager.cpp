// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "EnemySpawnPoint.h"
#include "Components/ActorComponent.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnRoot = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("SpawnRoot"));
	RootComponent = SpawnRoot;



	Spawner1 = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Spawner 1"));
	Spawner1->SetupAttachment(SpawnRoot);
	Spawner1->SetChildActorClass(AEnemySpawnPoint::StaticClass());
	Spawner1->SetRelativeLocation(FVector(200, 0, 0));

	Spawner2 = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Spawner 2"));
	Spawner2->SetupAttachment(SpawnRoot);
	Spawner2->SetChildActorClass(AEnemySpawnPoint::StaticClass());
	Spawner2->SetRelativeLocation(FVector(100, 100, 0));

	Spawner3 = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Spawner 3"));
	Spawner3->SetupAttachment(SpawnRoot);
	Spawner3->SetChildActorClass(AEnemySpawnPoint::StaticClass());
	Spawner3->SetRelativeLocation(FVector(-50, 80, 0));

	Spawner4 = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Spawner 4"));
	Spawner4->SetupAttachment(SpawnRoot);
	Spawner4->SetChildActorClass(AEnemySpawnPoint::StaticClass());
	Spawner4->SetRelativeLocation(FVector(-50, -80, 0));

	Spawner5 = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Spawner 5"));
	Spawner5->SetupAttachment(SpawnRoot);
	Spawner5->SetChildActorClass(AEnemySpawnPoint::StaticClass());
	Spawner5->SetRelativeLocation(FVector(100, -100, 0));

	for (int i = 0; i < 5; i++)
		SpawnerTypes.Add(EenemyType::None);
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	Cast<AEnemySpawnPoint>(Spawner1->GetChildActor())->SetEnemyType(SpawnerTypes[0]);
	Cast<AEnemySpawnPoint>(Spawner2->GetChildActor())->SetEnemyType(SpawnerTypes[1]);
	Cast<AEnemySpawnPoint>(Spawner3->GetChildActor())->SetEnemyType(SpawnerTypes[2]);
	Cast<AEnemySpawnPoint>(Spawner4->GetChildActor())->SetEnemyType(SpawnerTypes[3]);
	Cast<AEnemySpawnPoint>(Spawner5->GetChildActor())->SetEnemyType(SpawnerTypes[4]);


}

void ASpawnManager::SpawnSignal()
{
	Cast<AEnemySpawnPoint>(Spawner1->GetChildActor())->SpawnEnemyPrefab();
	Cast<AEnemySpawnPoint>(Spawner2->GetChildActor())->SpawnEnemyPrefab();
	Cast<AEnemySpawnPoint>(Spawner3->GetChildActor())->SpawnEnemyPrefab();
	Cast<AEnemySpawnPoint>(Spawner4->GetChildActor())->SpawnEnemyPrefab();
	Cast<AEnemySpawnPoint>(Spawner5->GetChildActor())->SpawnEnemyPrefab();
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

