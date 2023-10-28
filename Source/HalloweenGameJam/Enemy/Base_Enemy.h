// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include  "HalloweenGameJam/Entity_Stats.h"
#include "HalloweenGameJam/EnemyTypes.h"
#include "Base_Enemy.generated.h"

class ABase_Enemy_Controller;



UENUM(Blueprintable)
enum class EEnemyStates : uint8
{
	Idle,
	Moving,
	Attacking,
	Taunting,
	Death
};

USTRUCT(BlueprintType)
struct HALLOWEENGAMEJAM_API FEnemyData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EenemyType ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> ObjectMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ObjectScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABase_Enemy_Controller> ObjectController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimBlueprint> ObjectAnimation;


	FEnemyData() :ObjectType(EenemyType::None), ObjectMesh(nullptr), ObjectScale(FVector()), ObjectController(nullptr), ObjectAnimation(nullptr)
	{

	}
};


UCLASS()
class HALLOWEENGAMEJAM_API ABase_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateCollisionSize();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	EenemyType EnemyType;

	UPROPERTY()
	TObjectPtr<UDataTable> EnemyData;

	UPROPERTY()
	FEntity_Stats EnemyStats;

	UPROPERTY()
	TObjectPtr<UArrowComponent> EnemyDirection;



protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABase_Enemy_Controller> EnemyController;

	void LoadEnemyData(EenemyType);
	void FindEnemyTypeFromData(EenemyType);

public:
	FEntity_Stats GetEnemyStats()const { return  EnemyStats; }
	inline void DamageEnemy(const float Damage) { EnemyStats.Health -= Damage; }

};
