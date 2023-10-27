// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
ABase_Player::ABase_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Camera = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	CameraArm = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(GetCapsuleComponent());
	CameraArm->TargetArmLength = 300.f;



	Camera->SetupAttachment(CameraArm);
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


		// TODO add player firing to the game and damage the enemies
	}



}

void ABase_Player::Turn(const FInputActionValue& Value)
{
	FVector2D LookVec = Value.Get<FVector2D>();
	if (Controller)
	{

		AddControllerYawInput(LookVec.X);
		AddControllerPitchInput(LookVec.Y);
	}
}

void ABase_Player::FireWeapon(const FInputActionValue& Value)
{
	float triggerVal = Value.Get<float>();
	if (triggerVal >= 0.4f)
	{

		if (FHitResult* hitResult = LineTraceMethod(FVector(), FVector()))
		{
			// do hit logic here		
		}

		triggerVal = 0.f;
	}
}

FHitResult* ABase_Player::LineTraceMethod(const FVector& StartLocation, const FVector& EndLocation)
{
	FHitResult* HitResult = new FHitResult();
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), StartLocation, StartLocation + EndLocation, FColor::Purple, false, 1.f, 0, 2);

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartLocation, StartLocation + EndLocation, ECC_Visibility, CollisionParams))
	{
		return HitResult;

	}
	return HitResult;
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



