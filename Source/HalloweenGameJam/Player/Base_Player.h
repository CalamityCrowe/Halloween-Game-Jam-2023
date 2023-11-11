// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HalloweenGameJam/Entity_Stats.h"
#include "Base_Player.generated.h"

class UInputAction;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UDynamicMusicActor; 

UCLASS()
class HALLOWEENGAMEJAM_API ABase_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> FirePoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> RangeTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDynamicMusicActor> MusicActor; 

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	void Move(const FInputActionValue&);
	void Turn(const FInputActionValue&);
	void TriggerHeld() { bisHeld = true; };
	void TriggerReleased() { bisHeld = false; }

	void FireWeapon(float);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FEntity_Stats PlayerStats;


public:
	TObjectPtr<UCameraComponent> GetCamera() const { return Camera; }
	TObjectPtr<USpringArmComponent> GetCameraArm() const { return CameraArm; }

	FEntity_Stats GetPlayerStats()const { return PlayerStats; }

private:
	bool LineTraceMethod(FHitResult&);

	bool bisHeld;

	float triggerInterval = 0.4f;
	float timer;
};
