// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicMusicActor.generated.h"

UENUM()

enum class EMusicState : uint8
{
	None,
	Idle,
	CombatInitiated,
	Fighting
};

UENUM()

enum class ECombatPerformance: uint8
{
	None,
	Dope,
	Crazy,
	Badass,
	Apocalyptic,
	Savage,
	Sick_Skills,
	Smokin_Sexy_Style
};

UCLASS()
class HALLOWEENGAMEJAM_API ADynamicMusicActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicMusicActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HandlePerformanceState();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	float StyleMeter;
	float LowerCap;
	float IncreaseCap;
	float DefaultValue;

	float BaseVolume;
	float LowerVolume;
	float HigherVolume;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<EMusicState> CurrentMusicState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECombatPerformance> CurrentCombatPerformance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAudioComponent> BaseAudioTrack; 

public:
	EMusicState GetMusicState() const { return CurrentMusicState;  }
	void SetMusicState(EMusicState newState)  { CurrentMusicState = newState; }


};
