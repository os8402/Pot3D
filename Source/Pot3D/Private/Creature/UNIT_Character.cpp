#include "Creature/UNIT_Character.h"
#include "Animation/UNIT_Anim.h"

#include "Stat/ACP_StatInfo.h"
#include "Skill/ACP_SKillInfo.h"

#include "UI/WG_HpBar.h"
#include "UI/ACT_DamgeText.h"
#include "Manager/GI_GmInst.h"

#include "Controller/UNIT_PlayerCT.h"

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include <Components/SceneCaptureComponent2D.h>
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include <Kismet/KismetMathLibrary.h>
#include <kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>
#include <Components/AudioComponent.h>
#include <Sound/SoundCue.h>

// Sets default values
AUNIT_Character::AUNIT_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	_ACP_Stat = CreateDefaultSubobject<UACP_StatInfo>(TEXT("STAT"));
	_ACP_Weapon = CreateDefaultSubobject<UACP_Weapon>(TEXT("WEAPON"));

	UtilsLib::GetClass<AActor>(&_ACT_DmgText, TEXT("Blueprint'/Game/BluePrints/Object/DamageTextActor/BP_DmgTextActor.BP_DmgTextActor_C'"));

	_PS_HitEff = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));
	_PS_HitEff->SetupAttachment(GetMesh());
	FVector effPos = FVector(0.f, 0.f, 50.f);
	_PS_HitEff->SetRelativeLocation(effPos);
	_PS_HitEff->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HIT_EFF(TEXT("ParticleSystem'/Game/Resources/Models/ParagonGrux/FX/Particles/Abilities/Primary/FX/P_Grux_ApplyBleed.P_Grux_ApplyBleed'"));
	if (HIT_EFF.Succeeded())
	{
		_PS_HitEff->SetTemplate(HIT_EFF.Object);
		_PS_HitEff->bAutoActivate = false;

	}

}

void AUNIT_Character::BeginPlay()
{
	Super::BeginPlay();


	TArray<UMaterialInterface*> mats = GetMesh()->GetMaterials();
	int32 nums = GetMesh()->GetNumMaterials();

	for (int32 i = 0; i < nums; i++)
	{
		UMaterialInterface* mat = GetMesh()->GetMaterial(i);
		UMaterialInstanceDynamic* mid = UMaterialInstanceDynamic::Create(mat, this);
		GetMesh()->SetMaterial(i, mid);
		_MID_meshs.Add(mid);
	}

}

void AUNIT_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_ACP_Stat->SetCharacterId(_chrId);

	if(_ACP_Skill)
		_ACP_Skill->SetSkillData(_ACP_Stat->GetJob());

	_unitAnim = Cast<UUNIT_Anim>(GetMesh()->GetAnimInstance());

	if (_unitAnim)
	{
		_unitAnim->OnMontageEnded.AddDynamic(this, &AUNIT_Character::OnAttackMontageEnded);
		_unitAnim->OnMontageEnded.AddDynamic(this, &AUNIT_Character::OnSkillMontageEnded);
		_unitAnim->GetOnAttackHit().AddUObject(this, &AUNIT_Character::AttackAnimCheck);
		_unitAnim->GetOnSkillHit().AddUObject(this, &AUNIT_Character::SkillAnimCheck);
		_ACP_Stat->GetOnUnitDied().AddUObject(_unitAnim, &UUNIT_Anim::SetDead);
	}

	_ACP_Stat->GetOnUnitDied().AddUObject(this, &AUNIT_Character::SetUnitStates, EUnitStates::DEAD);


}

void AUNIT_Character::TickRecovery(float DeltaTime)
{	
	if(_UnitStates == EUnitStates::DEAD)
		return;

	_tickRecoveryTime += DeltaTime;

	if (_tickRecoveryTime >= 1.f)
	{
		int32 curHP = _ACP_Stat->GetHp();
		int32 maxHP = _ACP_Stat->GetMaxHp();
		int32 resilience = _ACP_Stat->GetResilience();
		
		if(curHP < maxHP)
			_ACP_Stat->SetHp(curHP + resilience);

		_tickRecoveryTime = 0.f;
	}
}

// Called every frame
void AUNIT_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickRecovery(DeltaTime);
	OnHitFlag(DeltaTime);

}

void AUNIT_Character::AttackEnemy()
{
	if (_bAttacking)
		return;

	_bAttacking = true;

	FVector ownedPos = GetActorLocation();
	FVector enemyPos = FVector::ZeroVector;

	if (GetTargetEnemy().IsValid() == false)
	{
		SetUnitStates(EUnitStates::DEAD);
		return;
	}

	enemyPos = _targetEnemy.Get()->GetActorLocation();
	FRotator destRot = UKismetMathLibrary::FindLookAtRotation(ownedPos, enemyPos);
	SetActorRotation(destRot);

	GetUnitAnim()->PlayMontageAnim();
	FName name = GetUnitAnim()->GetAttackMontageName(_attackIndex);
	GetUnitAnim()->JumpToSection(name);

	int32 maxAttackNum = GetUnitAnim()->GetMaxAttackNum();

	_attackIndex = (_attackIndex + 1) % maxAttackNum;

}

void AUNIT_Character::AttackAnimCheck()
{
	if (CanAttack() == false)
		return;

	FDamageEvent dmgEvent;
	int32 dmg = _ACP_Stat->CalcDamage();

	GetTargetEnemy().Get()->TakeDamage(dmg, dmgEvent, GetController(), this);

}


bool AUNIT_Character::CanAttack()
{

	if (GetTargetEnemy().IsValid() == false)
		return false;

	if (GetTargetEnemy().Get()->GetUnitStates() == EUnitStates::DEAD)
		return false;

	if (this->GetDistanceTo(GetTargetEnemy().Get()) > 300.f)
		return false;

	return true;

}


void AUNIT_Character::SkillAnimCheck()
{
	
	TArray<AUNIT_Character*> skillTargetEnemy = GetSkillComp()->GetSkillTargetEnemy();
	int32 skillId = GetSkillComp()->GetUsingSKillId();
	bool bAcquiredSkill = GetSkillComp()->IsAcquiredSkill(skillId);
	//스킬 사용 가능한 지 검사 
	if(skillTargetEnemy.Num() == 0 || bAcquiredSkill == false)
		return;
	//스킬 데이터
	FSkillData* skillData = GetSkillComp()->GetAcquireSKill(skillId);

	if(skillData == nullptr)
		return;
	//물리 + 마법 , 물리 + 디버프 등 조합이 다양할 수 있음.
	int32 skillTypeLen = skillData->_skillAttackTypes.Num();


	for (const auto& target : skillTargetEnemy)
	{
		if (target == nullptr)
			continue;

		UACP_StatInfo* statComp = target->GetStatComp();
		int32 hp = statComp->GetHp();
		int32 mp = statComp->GetMp();
			
		for (int32 i = 0; i < skillTypeLen; i++)
		{
			int32 value = skillData->_values[i];
			ESkillAttackTypes skillAttackType = skillData->_skillAttackTypes[i];

			//공격계열이나 
			if (skillAttackType == ESkillAttackTypes::MELEE || skillAttackType == ESkillAttackTypes::MAGIC)
			{
				if (hp <= 0)
					continue;

				UGameplayStatics::ApplyDamage(target, value, GetController(), this, NULL);
			}
			//회복계열
			else if (skillAttackType == ESkillAttackTypes::RECOVERY)
			{
				ERecoveryTypes recoveryType = skillData->_recoveryTypes[i];
				int32 newValue = 0;

				switch (recoveryType)
				{
				case ERecoveryTypes::HP:
					newValue = hp + value;
					statComp->SetHp(newValue);
					break;
				case ERecoveryTypes::MP:
					newValue = mp + value;
					statComp->SetMp(newValue);
					break;

				default:
					break;
				}

				AACT_DamgeText* dmgActor = UtilsLib::MakeSpawnActor<AACT_DamgeText>(GetWorld(), _ACT_DmgText, this);
				dmgActor->UpdateDamage(value, ESpawnTextTypes::HEAL);

			}
			//버프
			else if (skillAttackType == ESkillAttackTypes::BUFF)
			{
				
			}
			//디버프
			else if (skillAttackType == ESkillAttackTypes::DEBUFF)
			{

			}

		}

	}

}



void AUNIT_Character::OnAttackMontageEnded(UAnimMontage* montage, bool bInteruppted)
{
	_bAttacking = false;
	_onAttackEnded.Broadcast();
}

void AUNIT_Character::OnSkillMontageEnded(UAnimMontage* montage, bool bInteruppted)
{
	auto pc = Cast<AUNIT_PlayerCT>(GetController());

	if (pc)
		pc->SetSkillEnded();

	// 현재 사용 중인 스킬 정보 삭제
	GetSkillComp()->SetUsingSKillId(-1);

}

float AUNIT_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	float dmg = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int32  defence = _ACP_Stat->CalcDefence();

	dmg -= defence;


	int32 calcDmg = FMath::Max(0, (int32)dmg);

	_ACP_Stat->OnAttacked(calcDmg);

	//hp바 표시
	VisibleHpBar();

	ESpawnTextTypes spawnType = (GetStatComp()->GetUnitTypes() == EUnitTypes::PLAYER)
		? ESpawnTextTypes::DAMAGED_PLAYER
		: ESpawnTextTypes::DAMAGED_MONSTER;

	AACT_DamgeText* dmgActor = UtilsLib::MakeSpawnActor<AACT_DamgeText>(GetWorld(), _ACT_DmgText, this);
	dmgActor->UpdateDamage(calcDmg, spawnType);

	

	//Hit 이펙트
	_hitFlagGauge = 0.f;
	_bHitFlag = true;

	_PS_HitEff->Activate(true);

	return DamageAmount;
}


void AUNIT_Character::OnHitFlag(float DeltaTime)
{
	if(_UnitStates == EUnitStates::DEAD)
		return;

	if (_bHitFlag)
	{
		_hitFlagGauge += DeltaTime * _hitSpeed;

		if (_hitFlagGauge >= .9f)
		{
			_bHitFlag = false; 
			_hitFlagGauge = 0.f;
		}

		for (const auto& mid : _MID_meshs)
		{
			mid->SetScalarParameterValue(TEXT("Damage") , _hitFlagGauge);
		}
	}
}

void AUNIT_Character::UseActiveSKill(FName skillName)
{
	
	GetUnitAnim()->PlayMontageAnim();
	FName name = GetUnitAnim()->GetSkillMontageName(skillName);
	GetUnitAnim()->JumpToSection(name);

}

void AUNIT_Character::VisibleHpBar()
{


}


void AUNIT_Character::DeadUnit()
{
	UCapsuleComponent* capsuleComp = GetCapsuleComponent();

	if (capsuleComp != nullptr)
	{
		capsuleComp->DestroyComponent(true);
	}
	
	GetMesh()->SetCollisionProfileName("IgnoreOnlyPawn");

	USoundWave* deadSoundWav = GetStatComp()->GetUnitSound((int32)ECharacterSounds::DEAD);

	if(deadSoundWav)
		UtilsLib::SoundPlay(GetWorld(), deadSoundWav , GetActorLocation());

	for (const auto& mid : _MID_meshs)
		mid->SetScalarParameterValue(TEXT("Damage"), 0);

	SetOutline(false);


}

void AUNIT_Character::SetOutline(bool on)
{

	GetMesh()->SetRenderCustomDepth(on);
	int32 id = (on) ? 2 : 0;

	GetMesh()->SetCustomDepthStencilValue(id);


}

void AUNIT_Character::SetUnitStates(EUnitStates state)
{
	_UnitStates = state;

	switch (state)
	{
	case EUnitStates::IDLE :

		break;

	case EUnitStates::ATTACK:

		break;

	case EUnitStates::DEAD:
		DeadUnit();
		break; 

	}
}
