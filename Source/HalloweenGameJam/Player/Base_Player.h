// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Base_Player.generated.h"

class USpringArmComponent; 
class UCameraComponent; 

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
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraArm;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	void Move( const FInputActionValue&);
	void Turn( const FInputActionValue&);



public:
	TObjectPtr<UCameraComponent> GetCamera() const { return Camera;  }
	TObjectPtr<USpringArmComponent> GetCameraArm() const { return CameraArm;  }


};
