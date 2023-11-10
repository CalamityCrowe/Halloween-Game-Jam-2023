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


}

// Called when the game starts or when spawned
void ADynamicMusicActor::BeginPlay()
{
	Super::BeginPlay();

	BaseAudioTrack->SetSound(BaseTrack);
}

void ADynamicMusicActor::HandlePerformanceState()
{
	if (StyleMeter >= IncreaseCap)
	{

		StyleMeter = DefaultValue;
	}
	if (StyleMeter <= LowerCap)
	{

		StyleMeter = DefaultValue;
	}
}

// Called every frame
void ADynamicMusicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentMusicState)
	{
	case EMusicState::Fighting:
		HandlePerformanceState();
		break;

	default:

		break;

	}

}

