// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DynamicMusicActor.generated.h"

UENUM()

enum class EMusicState : uint8
{
	None,
	Idle,
	Fighting
};

UENUM()

enum class ECombatPerformance : uint8
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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HALLOWEENGAMEJAM_API UDynamicMusicActor : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UDynamicMusicActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HandlePerformanceState();



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float StyleMeter;

	float LowerCap;
	float IncreaseCap;
	float DefaultValue;

	float BaseVolume;
	float LowerVolume;
	float HigherVolume;

	float PerformanceDecreaseTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<EMusicState> CurrentMusicState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECombatPerformance> CurrentCombatPerformance;


	TArray<UAudioComponent*> CombatAudioPlayers;


	TObjectPtr<UAudioComponent> IdleAudioPlayer;
	TObjectPtr<UAudioComponent> CombatInitiatedAudioPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> IdleTrack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> CombatInitiatedTrack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<USoundBase*> CombatTracks;



public:
	EMusicState GetMusicState() const { return CurrentMusicState; }
	void SetMusicState(EMusicState NewState) { CurrentMusicState = NewState; }

	void IncreasePerformanceMeter(const float Increase) { StyleMeter += Increase; PerformanceDecreaseTimer = 0.f;  }





	void TransitionToIdle();
	void TransitionToCombatInitiated();
private:
	void IncreaseCombatPerformance();
	void DecreaseCombatPerformance();


};
