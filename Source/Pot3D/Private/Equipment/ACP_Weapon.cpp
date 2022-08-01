// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/ACP_Weapon.h"

#include <Particles/ParticleSystemComponent.h>

// Sets default values for this component's properties
UACP_Weapon::UACP_Weapon()
{

	PrimaryComponentTick.bCanEverTick = false;

	_PS_AttachEff = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ATTACH_PARTICLE"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACH_EFF(TEXT("ParticleSystem'/Game/Resources/Models/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Attach.P_Kwang_Sword_Attach'"));
	
	if (ATTACH_EFF.Succeeded())
		_temp_AttachEff = ATTACH_EFF.Object;

}


void UACP_Weapon::SoundPlay(USoundWave* wav)
{
	if (_Audio_Comp)
	{
		_Audio_Comp->SetSound(wav);
		_Audio_Comp->Play(0.f);
	}

}

