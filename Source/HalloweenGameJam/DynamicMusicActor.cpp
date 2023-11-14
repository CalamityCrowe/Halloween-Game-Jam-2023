// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMusicActor.h"

#include <string>

#include "Components/AudioComponent.h"


// Sets default values
UDynamicMusicActor::UDynamicMusicActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	BaseVolume = 0.5f;
	LowerVolume = 0.25f;
	HigherVolume = 1;

	StyleMeter = 0;
	IncreaseCap = 1.f;
	LowerCap = 0;
	DefaultValue = 0.5f;

	CurrentMusicState = EMusicState::None;
	CurrentCombatPerformance = ECombatPerformance::None;


	IdleAudioPlayer = CreateOptionalDefaultSubobject<UAudioComponent>(TEXT("IdlePlayer"));
	IdleAudioPlayer->SetupAttachment(this);

	CombatInitiatedAudioPlayer = CreateOptionalDefaultSubobject<UAudioComponent>(TEXT("InitiatedAudioPlayer"));
	CombatInitiatedAudioPlayer->SetupAttachment(this);

	for (int i = 0; i < 5; i++)
	{
		CombatAudioPlayers.Add(TObjectPtr<UAudioComponent>());

		CombatTracks.Add(TObjectPtr<USoundBase>());
	}

	CombatAudioPlayers[0] = CreateOptionalDefaultSubobject<UAudioComponent>("Combat Dope Player");
	CombatAudioPlayers[1] = CreateOptionalDefaultSubobject<UAudioComponent>("Combat Crazy Player");
	CombatAudioPlayers[2] = CreateOptionalDefaultSubobject<UAudioComponent>("Combat Badass Player");
	CombatAudioPlayers[3] = CreateOptionalDefaultSubobject<UAudioComponent>("Combat Apocalyptic Player");
	CombatAudioPlayers[4] = CreateOptionalDefaultSubobject<UAudioComponent>("Combat Sexy Player");


	for (int i = 0; i < 5; i++) { CombatAudioPlayers[i]->SetupAttachment(this); }

	//IdleAudioPlayer->SetVolumeMultiplier(BaseVolume);

}

// Called when the game starts or when spawned
void UDynamicMusicActor::BeginPlay()
{
	Super::BeginPlay();

	IdleAudioPlayer->SetSound(IdleTrack);
	IdleAudioPlayer->SetBoolParameter("Looping", true);

	for (int i = 0; i < CombatAudioPlayers.Num(); i++)
	{
		if (CombatTracks[i] != nullptr)
		{
			CombatAudioPlayers[i]->SetSound(CombatTracks[i]); //sets the combat racks to get used in the game
			CombatAudioPlayers[i]->SetBoolParameter("Looping", true);
		}

	}

	CombatInitiatedAudioPlayer->SetSound(CombatInitiatedTrack);

	IdleAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear);
	SetMusicState(EMusicState::Idle);

	//BaseAudioPlayer->FadeIn(3, 1, 0, EAudioFaderCurve::Linear); 
}

void UDynamicMusicActor::HandlePerformanceState()
{

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

	if (CurrentCombatPerformance == ECombatPerformance::None)
	{
		StyleMeter = 0.9f;
	}
}

// Called every frame
void UDynamicMusicActor::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformanceDecreaseTimer += DeltaTime;

	if (PerformanceDecreaseTimer >= 1.5f && CurrentCombatPerformance != ECombatPerformance::None)
	{
		StyleMeter -= DeltaTime / 4;
	}

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
	CombatInitiatedAudioPlayer->FadeIn(3, 100, 0, EAudioFaderCurve::Linear);
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



