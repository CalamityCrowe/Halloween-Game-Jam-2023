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


	for (int i = 0; i < 5; i++)
	{
		CombatAudioPlayers.Add(TObjectPtr<UAudioComponent>());
		CombatTracks.Add(TObjectPtr<USoundBase>());
	}

	//IdleAudioPlayer->SetVolumeMultiplier(BaseVolume);

}

// Called when the game starts or when spawned
void UDynamicMusicActor::BeginPlay()
{
	Super::BeginPlay();

	IdleAudioPlayer->SetSound(IdleTrack);
	IdleAudioPlayer->SetBoolParameter("Loop", true);
	IdleAudioPlayer->SetIntParameter(FName(TEXT("Combat Switch")), CurrentMusicState.GetIntValue());

	for (int i = 0; i < CombatAudioPlayers.Num(); i++)
	{
		if (CombatTracks[i] != nullptr)
		{
			CombatAudioPlayers[i]->SetSound(CombatTracks[i]); //sets the combat racks to get used in the game
		}

	}

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
	default:
		break;

	}
}

void UDynamicMusicActor::TransitionToIdle()
{
	for (int i = 0; i < CombatAudioPlayers.Num(); i++)
	{
		if (CombatAudioPlayers[i]->IsPlaying())
		{
			CombatAudioPlayers[i]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		}
	}
	if (CombatInitiatedAudioPlayer->IsPlaying())
	{
		CombatInitiatedAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
	}
	IdleAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
	CurrentMusicState = EMusicState::Idle;
}

void UDynamicMusicActor::TransitionToCombatInitiated()
{
	IdleAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
	CombatInitiatedAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
	CurrentMusicState = EMusicState::Fighting;
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
		CombatInitiatedAudioPlayer->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[0]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;
	case ECombatPerformance::Crazy:
		CombatAudioPlayers[0]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[1]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);

		break;
	case ECombatPerformance::Badass:
		CombatAudioPlayers[1]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[2]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;
	case ECombatPerformance::Apocalyptic:
		CombatAudioPlayers[2]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[3]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Savage:
	case ECombatPerformance::Sick_Skills:
	case ECombatPerformance::Smokin_Sexy_Style:
		if (PreviousState == ECombatPerformance::Apocalyptic)
		{
			CombatAudioPlayers[3]->FadeOut(3, 0, EAudioFaderCurve::Linear);
			CombatAudioPlayers[4]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
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
		CombatAudioPlayers[0]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatInitiatedAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Dope:
		CombatAudioPlayers[1]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[0]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Crazy:
		CombatAudioPlayers[2]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[1]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);

		break;
	case ECombatPerformance::Badass:
		CombatAudioPlayers[3]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[2]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;
	case ECombatPerformance::Apocalyptic:

		CombatAudioPlayers[4]->FadeOut(3, 0, EAudioFaderCurve::Linear);
		CombatAudioPlayers[3]->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
		break;

	case ECombatPerformance::Savage:
	case ECombatPerformance::Sick_Skills:
	case ECombatPerformance::Smokin_Sexy_Style:

		break;

	default:
		break;
	}
}



