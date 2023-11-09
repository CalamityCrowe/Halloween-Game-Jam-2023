// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMusicActor.h"

// Sets default values
ADynamicMusicActor::ADynamicMusicActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseAudioTrack = CreateOptionalDefaultSubobject<UAudioComponent>(TEXT(""))


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

}

