// Fill out your copyright notice in the Description page of Project Settings.


#include "ACP_Weapon.h"
#include <Components/AudioComponent.h>
#include <Sound/SoundCue.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values for this component's properties
UACP_Weapon::UACP_Weapon()
{

	PrimaryComponentTick.bCanEverTick = false;

	_Audio_Comp = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO_COMP"));
	_Audio_Comp->bIsPaused = true;
	_Audio_Comp->bIsPaused = false;


	_PS_AttachEff = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ATTACH_PARTICLE"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACH_EFF(TEXT("ParticleSystem'/Game/Resources/Models/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Attach.P_Kwang_Sword_Attach'"));
	
	if (ATTACH_EFF.Succeeded())
		_temp_AttachEff = ATTACH_EFF.Object;

}


// Called when the game starts
void UACP_Weapon::BeginPlay()
{
	Super::BeginPlay();


	
}


void UACP_Weapon::SoundPlay(int32 index)
{

	if (_Audio_Comp)
	{
		_Audio_Comp->SetSound(_SOUND_WEPAON_Lists[index]);
		_Audio_Comp->Play(0.f);
	}
}

