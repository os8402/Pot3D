// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/UNIT_Player.h"
#include "Creature/UNIT_Monster.h"
#include "Controller/UNIT_PlayerCT.h"

#include "Equipment/ACP_Weapon.h"
#include "Item/ACT_DropItem.h"

#include "Equipment/ACP_Weapon.h"
#include "Equipment/ACP_Armor.h"

#include "Skill/ACP_SKillInfo.h"
#include "Fade/ACP_PlayerToCameraChecker.h"

#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include <Particles/ParticleSystemComponent.h>


AUNIT_Player::AUNIT_Player()
{

	GetMesh()->SetCollisionProfileName(TEXT("Player"));

	_ACP_Armor = CreateDefaultSubobject<UACP_Armor>(TEXT("ARMOR"));
	_ACP_Helmet = CreateDefaultSubobject<UACP_Armor>(TEXT("HELMET"));
	_ACP_Pants = CreateDefaultSubobject<UACP_Armor>(TEXT("PANTS"));
	_ACP_Boots = CreateDefaultSubobject<UACP_Armor>(TEXT("BOOTS"));

	_armorList.Add((int32)EItemArmorTypes::ARMOR, _ACP_Armor);
	_armorList.Add((int32)EItemArmorTypes::HELMET, _ACP_Helmet);
	_armorList.Add((int32)EItemArmorTypes::PANTS, _ACP_Pants);
	_armorList.Add((int32)EItemArmorTypes::BOOTS, _ACP_Boots);

	_SPC_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPC_ARM"));
	_SPC_Arm->SetupAttachment(GetCapsuleComponent());
	_SPC_Arm->SetUsingAbsoluteRotation(true);
	_SPC_Arm->TargetArmLength = _targetArmLength;
	_SPC_Arm->SetRelativeRotation(FRotator(-60.f, 45.f, 0.f));
	_SPC_Arm->bDoCollisionTest = false;

	GetCapsuleComponent()->SetCollisionProfileName("Player");

	_CAM_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("CAM"));
	_CAM_Cam->SetupAttachment(_SPC_Arm);
	_CAM_Cam->bUsePawnControlRotation = false;

	_ACP_CameraChecker = CreateDefaultSubobject<UACP_PlayerToCameraChecker>(TEXT("CAMERA_CHECKER"));


}

void AUNIT_Player::BeginPlay()
{
	Super::BeginPlay();

	_ACP_Weapon->SetOwner(this);

	for (auto& item : _armorList)
		item.Value->SetOwner(this);


}

void AUNIT_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SearchActorInfo();
}


void AUNIT_Player::SearchActorInfo()
{
	if (GetUnitStates() == EUnitStates::DEAD)
		return;

	auto pc = Cast<AUNIT_PlayerCT>(GetController());

	if (pc)
	{
		FHitResult hitOther;
		pc->GetHitResultUnderCursor(ECC_GameTraceChannel5, false, hitOther);

		FHitResult hitItem;
		pc->GetHitResultUnderCursor(ECC_GameTraceChannel3, false, hitItem);


		if (hitOther.bBlockingHit)
		{
			//캐릭터 [ 몬스터, npc = 추후 멀티 추가되면 플레이어도 넣긴 할듯]
			auto other = Cast<AUNIT_Character>(hitOther.Actor);
			pc->LookActorOther(other);
		}

		if (hitItem.bBlockingHit)
		{
			//드랍 아이템 확인
			auto dropItem = Cast<AACT_DropItem>(hitItem.Actor);

			pc->LookDropItem(dropItem);
		}

	}
}

void AUNIT_Player::AttackAnimCheck()
{
	Super::AttackAnimCheck();

	auto pc = Cast<AUNIT_PlayerCT>(GetController());
	
	if (pc)
	{
		ECameraShake cameraType = ECameraShake::NORMAL;
		pc->CameraShake(cameraType, .5f);
	}
		
}

void AUNIT_Player::SkillAnimCheck()
{
	Super::SkillAnimCheck();

	auto pc = Cast<AUNIT_PlayerCT>(GetController());

	if (pc)
	{
		ECameraShake cameraType = ECameraShake::EARTH_QUAKE;
		pc->CameraShake(cameraType, 1.0f);
	}
}

void AUNIT_Player::GetReward(int32 id)
{
	

}

