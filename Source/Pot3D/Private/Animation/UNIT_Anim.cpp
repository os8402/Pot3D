// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UNIT_Anim.h"
#include "Creature/UNIT_Character.h"
#include "Creature/UNIT_Player.h"
#include "Equipment/ACP_Weapon.h"


void UUNIT_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		_speed = pawn->GetVelocity().Size();
	}

}

void UUNIT_Anim::PlayMontageAnim()
{
	Montage_Play(_AM_attackMontage);
}

void UUNIT_Anim::JumpToSection(FName name)
{
	Montage_JumpToSection(name , _AM_attackMontage);
}

FName UUNIT_Anim::GetAttackMontageName(int32 index)
{
	return FName(*FString::Printf(TEXT("Attack%d"), index));
}

FName UUNIT_Anim::GetSkillMontageName(FName name)
{
	return FName(*FString::Printf(TEXT("Skill_%s"), *name.ToString()));
}

void UUNIT_Anim::AnimNotify_AttackHit()
{
	_onAttackHit.Broadcast();
}

void UUNIT_Anim::AnimNotify_SkillHit()
{
	_onSKillHit.Broadcast();
}

void UUNIT_Anim::AnimNotify_SoundPlay()
{
	auto owner = Cast<AUNIT_Character>(TryGetPawnOwner());

	if (owner)
	{
		owner->SoundPlay((int)ECharacterSounds::NORMAL);

		auto player = Cast<AUNIT_Player>(owner);
		if(player)
			player->GetWeapon()->SoundPlay((int)EWeaponSounds::NORMAL);
	}
		
}

