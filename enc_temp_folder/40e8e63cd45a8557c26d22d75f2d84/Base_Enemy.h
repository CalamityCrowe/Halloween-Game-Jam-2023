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
enum  EEnemyStates : uint8
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
	TObjectPtr<UAnimBlueprint> ObjectAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ObjectSpeed;

	FEnemyData() :ObjectType(EenemyType::None), ObjectMesh(nullptr), ObjectScale(FVector()), ObjectAnimation(nullptr), ObjectSpeed(0)
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

	TObjectPtr<class ABase_Player> PlayerRef;

	void HandleEnemyDeath();
	void HandleEnemyStates();


protected:


	void LoadEnemyData(EenemyType);
	void FindEnemyTypeFromData(EenemyType);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<EEnemyStates> CurrentState;

public:
	FEntity_Stats GetEnemyStats()const { return  EnemyStats; }
	inline void DamageEnemy(const float Damage) { EnemyStats.Health -= Damage; }

	ABase_Player* GetPlayer()const { return PlayerRef; }

	TEnumAsByte<EEnemyStates> GetState() { return CurrentState; }

};
