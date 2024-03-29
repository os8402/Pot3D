// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UNIT_Anim.h"
#include "Creature/UNIT_Character.h"
#include "Creature/UNIT_Player.h"
#include "Equipment/ACP_Weapon.h"
#include "Skill/ACP_SKillInfo.h"
#include "Stat/ACP_StatInfo.h"
#include "Item/OBJ_Item.h"

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

	auto owner = Cast<AUNIT_Character>(TryGetPawnOwner());

	//무기에다가 싸운드 추가하고 넣어야함..
	UACP_Weapon* weapon = owner->GetWeapon();
	UOBJ_Item* item = weapon->GetItem();
	USoundWave* weaponSound = (item) ? item->GetVFXSound() : weapon->GetDefaultSound();

	UtilsLib::SoundPlay(GetWorld(), weaponSound , owner->GetActorLocation());

}

void UUNIT_Anim::AnimNotify_SkillHit()
{
	_onSKillHit.Broadcast();

}

void UUNIT_Anim::AnimNotify_SoundPrimaryAttack()
{
	auto owner = Cast<AUNIT_Character>(TryGetPawnOwner());

	if (owner)
	{
		UACP_StatInfo* statComp = owner->GetStatComp();
		USoundWave* primaryAtkSound = statComp->GetUnitSound((int32)ECharacterSounds::ATTACK);

		UtilsLib::SoundPlay(GetWorld(), primaryAtkSound, owner->GetActorLocation());

	}
}

void UUNIT_Anim::AnimNotify_SoundSkillAttack()
{

	auto owner = Cast<AUNIT_Character>(TryGetPawnOwner());

	if(owner == nullptr)
		return;

	UACP_SKillInfo* skillComp = owner->GetSkillComp();
	int32 usingSKill = skillComp->GetUsingSKillId();

	if(usingSKill == -1)
		return;

	USoundWave* unitSound = skillComp->GetSoundCharSound(usingSKill);

	UtilsLib::SoundPlay(GetWorld(), unitSound, owner->GetActorLocation());



}

void UUNIT_Anim::AnimNotify_PlayEffect()
{
	auto owner = Cast<AUNIT_Character>(TryGetPawnOwner());

	if (owner == nullptr)
		return;

	UACP_SKillInfo* skillComp = owner->GetSkillComp();
	int32 usingSKill = skillComp->GetUsingSKillId();

	if (usingSKill == -1)
		return;

	USoundWave* vfxSound = skillComp->GetSoundVFXSound(usingSKill);

	if (vfxSound)
		UtilsLib::SoundPlay(GetWorld(), vfxSound, owner->GetActorLocation());

	skillComp->PlaySkillEffect(usingSKill);
}
