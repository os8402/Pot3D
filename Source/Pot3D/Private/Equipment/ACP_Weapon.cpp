// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/ACP_Weapon.h"

#include <Particles/ParticleSystemComponent.h>

// Sets default values for this component's properties
UACP_Weapon::UACP_Weapon()
{

	PrimaryComponentTick.bCanEverTick = false;

	_PS_AttachEff = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ATTACH_PARTICLE"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACH_EFF(TEXT("ParticleSystem'/Game/Resources/Models/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Attach.P_Kwang_Sword_Attach'"));
	//
	//if (ATTACH_EFF.Succeeded())
	//	_temp_AttachEff = ATTACH_EFF.Object;


	UtilsLib::GetAsset<UParticleSystem>(&_temp_AttachEff, "ParticleSystem'/Game/Resources/Models/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Attach.P_Kwang_Sword_Attach'");
	UtilsLib::GetAsset<USoundWave>(&_defaultWav, TEXT("SoundWave'/Game/Resources/Sounds/SFX_Hammer_002_.SFX_Hammer_002_'"));

}


