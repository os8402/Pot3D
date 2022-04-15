// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/UNIT_Player.h"
#include "Creature/UNIT_Monster.h"
#include "Controller/UNIT_PlayerCT.h"
#include "ACP_Weapon.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include <Particles/ParticleSystemComponent.h>


AUNIT_Player::AUNIT_Player()
{
	SetUnitTypes(EUnitTypes::PLAYER);

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
	_PSPR_MinimapIcon->SetSpriteColor(FLinearColor::Green);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Resources/Models/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC'"));
	if (SM.Succeeded())
		GetMesh()->SetSkeletalMesh(SM.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACH_EFF(TEXT("ParticleSystem'/Game/Resources/Models/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Attach.P_Kwang_Sword_Attach'"));
	if (ATTACH_EFF.Succeeded())
	{
		FName FX_Electric(TEXT("FX_Electric"));
		if (GetMesh()->DoesSocketExist(FX_Electric))
		{

			GetWeapon()->GetAttachEffComp()->SetTemplate(ATTACH_EFF.Object);
			GetWeapon()->GetAttachEffComp()->SetupAttachment(GetMesh(), FX_Electric);

		}
	}

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
		FHitResult hitResult;
		pc->GetHitResultUnderCursor(ECC_Pawn, true, hitResult);

		if (hitResult.bBlockingHit)
		{
			auto obj = Cast<AUNIT_Character>(hitResult.Actor);
			pc->CheckActorOther(obj);
		}


	}
}

void AUNIT_Player::AttackCheck()
{
	Super::AttackCheck();

	if (CanAttack() == false)
		return;
	
	auto pc = Cast<AUNIT_PlayerCT>(GetController());
	
	if (pc)
		pc->CameraShake(1.0f);
}



void AUNIT_Player::GetReward(int32 id)
{


}

