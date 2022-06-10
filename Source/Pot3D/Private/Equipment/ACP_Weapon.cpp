// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/ACP_Weapon.h"
#include "Item/OBJ_Item.h"
#include "Stat/ACP_StatInfo.h"
#include "Creature/UNIT_Character.h"


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

void UACP_Weapon::SetEquipWeapon(UOBJ_Item* item)
{	
	_currentWeapon = item;

	_currentOwner->GetStatComp()->RefreshStat();

}

void UACP_Weapon::SoundPlay(int32 index)
{
	if (_Audio_Comp)
	{
		_Audio_Comp->SetSound(_SOUND_WEPAON_Lists[index]);
		_Audio_Comp->Play(0.f);
	}
}

