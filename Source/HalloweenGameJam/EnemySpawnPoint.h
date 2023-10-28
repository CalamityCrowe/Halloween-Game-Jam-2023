// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "EnemyTypes.h"
#include "EnemySpawnPoint.generated.h"


class ABase_Enemy;
class UArrowComponent; 


USTRUCT(BlueprintType)
struct HALLOWEENGAMEJAM_API FEnemyPrefabData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EenemyType ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ABase_Enemy> ObjectPrefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ObjectHealth;

	FEnemyPrefabData() :ObjectType(EenemyType::None), ObjectPrefab(nullptr), ObjectHealth(0)
	{

	}
};


UCLASS()
class HALLOWEENGAMEJAM_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Reference")
		EenemyType EnemyType;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		TObjectPtr<USceneComponent> EnemySpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<ABase_Enemy> EnemyReference;
	UPROPERTY()
		TObjectPtr<UDataTable> EnemyData;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UArrowComponent> SpawnDirection;

	void LoadEnemyPrefabDataTable();
	void LoadEnemyPrefab(EenemyType);

	float EnemyHealth;

public:
	USceneComponent* GetSpawnPoint() const { return EnemySpawn; }

	void SetEnemyType(EenemyType newEnemy) { EnemyType = newEnemy;  };

};
