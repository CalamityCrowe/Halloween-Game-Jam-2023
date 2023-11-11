// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMusicActor.h"
#include "Components/AudioComponent.h"


// Sets default values
UDynamicMusicActor::UDynamicMusicActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

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
void UDynamicMusicActor::BeginPlay()
{
	Super::BeginPlay();

	IdleAudioPlayer->SetSound(BaseTrack);
	IdleAudioPlayer->SetBoolParameter("Loop", true);
	IdleAudioPlayer->SetIntParameter(FName(TEXT("Combat Switch")), CurrentMusicState.GetIntValue());

	//BaseAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear); 
}

void UDynamicMusicActor::HandlePerformanceState()
{
	if (CurrentCombatPerformance == ECombatPerformance::None)
	{
		StyleMeter = 0.9f;
	}

	if (StyleMeter >= IncreaseCap)
	{
		IncreaseCombatPerformance();
		StyleMeter = DefaultValue;
	}
	if (StyleMeter <= LowerCap)
	{
		DecreaseCombatPerformance();
		StyleMeter = DefaultValue;
	}
}

// Called every frame
void UDynamicMusicActor::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (CurrentMusicState.GetValue())
	{
	case EMusicState::Fighting:

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

void UDynamicMusicActor::IncreaseCombatPerformance()
{
	ECombatPerformance PreviousState = CurrentCombatPerformance.GetValue();
	if (CurrentCombatPerformance != ECombatPerformance::Smokin_Sexy_Style)
	{
		CurrentCombatPerformance = static_cast<ECombatPerformance>(CurrentCombatPerformance.GetIntValue() + 1);
	}
	switch (CurrentCombatPerformance.GetValue())
	{
	case ECombatPerformance::Dope:
		IdleAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatDopeAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;
	case ECombatPerformance::Crazy:
		CombatDopeAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatCrazyAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);

		break;
	case ECombatPerformance::Badass:
		CombatCrazyAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatBadassAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;
	case ECombatPerformance::Apocalyptic:
		CombatBadassAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatApocalypticAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Savage:
	case ECombatPerformance::Sick_Skills:
	case ECombatPerformance::Smokin_Sexy_Style:
		if (PreviousState == ECombatPerformance::Apocalyptic)
		{
			CombatApocalypticAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
			CombatSexyAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		}
		break;

	default:
		break;
	}

}

void UDynamicMusicActor::DecreaseCombatPerformance()
{
	if (CurrentCombatPerformance != ECombatPerformance::None)
	{
		CurrentCombatPerformance = static_cast<ECombatPerformance>(CurrentCombatPerformance.GetIntValue() - 1);
	}
	switch (CurrentCombatPerformance.GetValue())
	{
	case ECombatPerformance::None:
		CombatDopeAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		IdleAudioPlayer->FadeIn(3, BaseVolume, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Dope:
		CombatCrazyAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatDopeAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Crazy:
		CombatBadassAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatCrazyAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;
	case ECombatPerformance::Badass:
		CombatApocalypticAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatBadassAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;
	case ECombatPerformance::Apocalyptic:
		CombatSexyAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatApocalypticAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Savage:
	case ECombatPerformance::Sick_Skills:
	case ECombatPerformance::Smokin_Sexy_Style:

		break;

	default:
		break;
	}
}



