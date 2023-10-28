// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Enemy.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABase_Enemy::ABase_Enemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyDirection = CreateOptionalDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	EnemyDirection->SetupAttachment(RootComponent);

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	
	
}

// Called when the game starts or when spawned
void ABase_Enemy::BeginPlay()
{
	Super::BeginPlay();

	UpdateCollisionSize();
}

void ABase_Enemy::UpdateCollisionSize()
{
	FBoxSphereBounds MeshBounds{ GetMesh()->SkeletalMesh->GetBounds() };
	FVector Scale3D{ GetMesh()->GetRelativeScale3D() };
	float newRadius = (((float)MeshBounds.BoxExtent.X + (float)MeshBounds.BoxExtent.Y) / 2.0f) * 0.5f * FMath::Max(Scale3D.X, Scale3D.Y);

	float BoxHeightConversionFactor{ 1.324f };        // conversion factor based on known good capsule height from UE3 prototype.
	float newHalfHeight{ (float)MeshBounds.BoxExtent.Z * 0.5f * BoxHeightConversionFactor * (float)Scale3D.Z };

	GetCapsuleComponent()->SetCapsuleSize(newRadius, newHalfHeight);
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
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
		GetMesh()->SetSkeletalMesh(FoundRow->ObjectMesh);
		SetActorScale3D(FoundRow->ObjectScale);
		EnemyController = FoundRow->ObjectController;
		GetMesh()->SetAnimInstanceClass(FoundRow->ObjectAnimation->GeneratedClass);
	}
}

