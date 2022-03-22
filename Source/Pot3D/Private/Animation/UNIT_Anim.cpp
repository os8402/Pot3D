// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UNIT_Anim.h"
#include "Creature/UNIT_Character.h"
#include "ACP_Weapon.h"


void UUNIT_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		_speed = pawn->GetVelocity().Size();
	}

}

void UUNIT_Anim::PlayAttackMontage()
{
	Montage_Play(_AM_attackMontage);
}

void UUNIT_Anim::AnimNotify_AttackHit()
{
	_onAttackHit.Broadcast();
}

void UUNIT_Anim::AnimNotify_SoundPlay()
{
	auto owner = Cast<AUNIT_Character>(TryGetPawnOwner());

	if (owner)
	{
		owner->SoundPlay((int)ECharacterSounds::NORMAL);
		owner->GetWeapon()->SoundPlay((int)EWeaponSounds::NORMAL);
	}
		
}

