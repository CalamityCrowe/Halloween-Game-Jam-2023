// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Base_Enemy.generated.h"

UENUM()
enum class EenemyType : uint8
{
	None,
	Ghoul,
	Goblin,
	Lich,
	Skeleton,
	Zombie
};

USTRUCT(BlueprintType)
struct HALLOWEENGAMEJAM_API FEnemyData: public FTableRowBase
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EenemyType ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> ObjectMesh; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ObjectScale;


	FEnemyData() :ObjectType(EenemyType::None), ObjectMesh(nullptr), ObjectScale(FVector())
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	EenemyType EnemyType;

	TObjectPtr<UDataTable> EnemyData; 

protected:

	void LoadEnemyData(EenemyType);
	void FindEnemyTypeFromData(EenemyType); 

};
