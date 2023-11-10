// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMusicActor.h"
#include "Components/AudioComponent.h"


// Sets default values
ADynamicMusicActor::ADynamicMusicActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BaseVolume = 0.5f;
	LowerVolume = 0.25f;
	HigherVolume = 1;

	StyleMeter = 0;
	IncreaseCap = 1.f;
	LowerCap = 0;
	DefaultValue = 0.5f;

	CurrentMusicState = EMusicState::None;
	CurrentCombatPerformance = ECombatPerformance::None;

	//IdleAudioPlayer->SetVolumeMultiplier(BaseVolume);

}

// Called when the game starts or when spawned
void ADynamicMusicActor::BeginPlay()
{
	Super::BeginPlay();

	BaseAudioPlayer->SetSound(BaseTrack);
	BaseAudioPlayer->SetBoolParameter("Loop", true);
	BaseAudioPlayer->SetIntParameter(FName(TEXT("Combat Switch")), CurrentMusicState.GetIntValue());
}

void ADynamicMusicActor::HandlePerformanceState()
{
	if (CurrentCombatPerformance == ECombatPerformance::None)
	{
		StyleMeter = 0.9f;
	}

	if (StyleMeter >= IncreaseCap)
	{
		IncreaseStyleMeter();
		StyleMeter = DefaultValue;
	}
	if (StyleMeter <= LowerCap)
	{
		DecreaseStyleMeter();
		StyleMeter = DefaultValue;
	}
}

// Called every frame
void ADynamicMusicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentMusicState.GetValue())
	{
	case EMusicState::Fighting:
		if (BaseAudioPlayer->IsPlaying() == false)
		{
			BaseAudioPlayer->Play();
		}

		HandlePerformanceState();

		break;

	case EMusicState::Idle:
		if (IdleAudioPlayer->IsPlaying() == false)
		{
			IdleAudioPlayer->Play();
		}
		break;

	case EMusicState::CombatInitiated:


		break;

	default:

		break;

	}
}

void ADynamicMusicActor::IncreaseStyleMeter()
{
	if (CurrentCombatPerformance != ECombatPerformance::Smokin_Sexy_Style)
	{
		CurrentCombatPerformance = static_cast<ECombatPerformance>(CurrentCombatPerformance.GetIntValue() + 1);
	}

}

void ADynamicMusicActor::DecreaseStyleMeter()
{
	if (CurrentCombatPerformance != ECombatPerformance::None)
	{
		CurrentCombatPerformance = static_cast<ECombatPerformance>(CurrentCombatPerformance.GetIntValue() - 1);
	}
}



