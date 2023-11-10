// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HalloweenGameJam/Enemy/Base_Enemy.h"
#include "HalloweenGameJam/Enemy/Lich.h"
#include "HalloweenGameJam/Enemy/Ghoul.h"


// Sets default values
ABase_Player::ABase_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Camera = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	CameraArm = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(GetCapsuleComponent());
	CameraArm->TargetArmLength = 300.f;

	FirePoint = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Fire Point"));
	FirePoint->SetupAttachment(GetCapsuleComponent());

	Camera->SetupAttachment(CameraArm);

	bisHeld = false;
}

// Called when the game starts or when spawned
void ABase_Player::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABase_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bisHeld)
	{
		FireWeapon(DeltaTime);
	}
}

// Called to bind functionality to input
void ABase_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABase_Player::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABase_Player::Turn);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ABase_Player::TriggerHeld);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ABase_Player::TriggerReleased);
	}

}

void ABase_Player::Turn(const FInputActionValue& Value)
{
	const FVector2D LookVec = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookVec.X);
		AddControllerPitchInput(LookVec.Y);
	}
}

void ABase_Player::FireWeapon(float DeltaTime)
{
	timer += DeltaTime;
	if (timer >= triggerInterval)
	{
		FHitResult hitResult;

		if (LineTraceMethod(hitResult))
		{
			// do hit logic here	
			if (hitResult.GetActor()->IsA<ABase_Enemy>())
			{
				ABase_Enemy* enemy = Cast<ABase_Enemy>(hitResult.GetActor());
				enemy->DamageEnemy(10.f);
				GEngine->AddOnScreenDebugMessage(110, 2, FColor::Yellow, TEXT("Hit"));

			}
		}



		timer = 0.f;
	}
}

bool ABase_Player::LineTraceMethod(FHitResult& OutHit)
{
	FVector start = FirePoint->GetComponentLocation();
	FVector end = start + Camera->GetForwardVector() * 10000;


	DrawDebugLine(GetWorld(), start, end, FColor::Purple, false, 1.f, 0, 2);

	FCollisionQueryParams parameters;

	parameters.AddIgnoredActor(this);


	return GetWorld()->LineTraceSingleByChannel(OutHit, start, end, ECC_Visibility, parameters);

}

void ABase_Player::Move(const FInputActionValue& Value)
{
	FVector2D moveVal = Value.Get<FVector2D>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), moveVal.Y);
		AddMovementInput(GetActorRightVector(), moveVal.X);
	}
}



