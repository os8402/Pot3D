// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/UNIT_Character.h"
#include "Animation/UNIT_Anim.h"
#include "Stat/ACP_StatInfo.h"
#include "UI/WG_HpBar.h"
#include "UI/ACT_DamgeText.h"
#include "Manager/GI_GmInst.h"

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
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SetCharJobs(EUnitJobs::WARRIOR);

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	_ACP_Stat = CreateDefaultSubobject<UACP_StatInfo>(TEXT("STAT"));



	static ConstructorHelpers::FClassFinder<AActor> DTC(TEXT("Blueprint'/Game/BluePrints/Object/DamageTextActor/BP_DmgTextActor.BP_DmgTextActor_C'"));

	if (DTC.Succeeded())
		_ACT_DmgText = DTC.Class;


	_SPR_MinimapSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("MINIMAP_SPRING"));
	_SPR_MinimapSpring->SetupAttachment(GetCapsuleComponent());
	_SPR_MinimapSpring->SetUsingAbsoluteRotation(true);
	_SPR_MinimapSpring->bInheritPitch = false;
	_SPR_MinimapSpring->bInheritRoll = false;
	_SPR_MinimapSpring->bInheritYaw = false;
	_SPR_MinimapSpring->TargetArmLength = 800.f;
	_SPR_MinimapSpring->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	_SPR_MinimapSpring->bDoCollisionTest = false;

	_SC_MinimapCam = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MINIMAP_CAM"));
	_SC_MinimapCam->SetupAttachment(_SPR_MinimapSpring);

	_PSPR_MinimapIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MINIMAP_ICON"));

	static ConstructorHelpers::FObjectFinder<UPaperSprite> PSPR(TEXT("PaperSprite'/Game/Resources/UI/Minimap/Minimap_Icon_Sprite.Minimap_Icon_Sprite'"));

	if (PSPR.Succeeded())
		_PSPR_MinimapIcon->SetSprite(PSPR.Object);

	_PSPR_MinimapIcon->SetupAttachment(GetCapsuleComponent());
	_PSPR_MinimapIcon->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	_PSPR_MinimapIcon->SetRelativeLocation(FVector(0.f, 0.f, 750.f));
	_PSPR_MinimapIcon->bOwnerNoSee = true;

	_Audio_Comp = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO_COMP"));
	_Audio_Comp->SetupAttachment(RootComponent);
	_Audio_Comp->bIsPaused = true;
	_Audio_Comp->bIsPaused = false;

	_PS_HitEff = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));
	_PS_HitEff->SetupAttachment(GetMesh());
	FVector effPos = FVector(0.f, 0.f, 50.f);
	_PS_HitEff->SetRelativeLocation(effPos);
	_PS_HitEff->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));


	static ConstructorHelpers::FObjectFinder<UParticleSystem> HIT_EFF(TEXT("ParticleSystem'/Game/Resources/Models/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact'"));

	if (HIT_EFF.Succeeded())
	{
		_PS_HitEff->SetTemplate(HIT_EFF.Object);
		_PS_HitEff->bAutoActivate = false;

	}
}

// Called when the game starts or when spawned
void AUNIT_Character::BeginPlay()
{
	Super::BeginPlay();


}


void AUNIT_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_ACP_Stat->SetCharacterId(_chrId);

	_unitAnim = Cast<UUNIT_Anim>(GetMesh()->GetAnimInstance());

	if (_unitAnim)
	{
		_unitAnim->OnMontageEnded.AddDynamic(this, &AUNIT_Character::OnAttackMontageEnded);
		_unitAnim->GetOnAttackHit().AddUObject(this, &AUNIT_Character::AttackCheck);
		_ACP_Stat->GetOnUnitDied().AddUObject(_unitAnim, &UUNIT_Anim::SetDead);
	}

	_ACP_Stat->GetOnUnitDied().AddUObject(this, &AUNIT_Character::SetUnitStates, EUnitStates::DEAD);


}

// Called every frame
void AUNIT_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	GetUnitAnim()->PlayAttackMontage();
	GetUnitAnim()->JumpToSection(_attackIndex);

	int32 maxAttackNum = GetUnitAnim()->GetMaxAttackNum();

	_attackIndex = (_attackIndex + 1) % maxAttackNum;

}

void AUNIT_Character::AttackCheck()
{

	if (CanAttack() == false)
		return;

	FDamageEvent dmgEvent;
	int32 minAtk = _ACP_Stat->GetMinAttack();
	int32 maxAtk = _ACP_Stat->GetMaxAttack();
	int32 dmg = FMath::RandRange(minAtk, maxAtk);

	GetTargetEnemy().Get()->TakeDamage(dmg, dmgEvent, GetController(), this);

}

void AUNIT_Character::SoundPlay(int32 index)
{

	if (_Audio_Comp)
	{
		_Audio_Comp->SetSound(_SOUND_CHAR_Lists[index]);
		_Audio_Comp->Play(0.f);
	}
	
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

void AUNIT_Character::OnAttackMontageEnded(UAnimMontage* montage, bool bInteruppted)
{
	_bAttacking = false;
	GetOnAttackEnded().Broadcast();
}

float AUNIT_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//
	float dmg =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//TODO : 능력치 합산 들어가야 함. 



	_ACP_Stat->OnAttacked(DamageAmount);

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	FVector spawnPos = GetActorLocation();
	FRotator spawnRot = DamageCauser->GetActorRotation();

	//Todo 데미지 띄우기
	UE_LOG(LogTemp, Log , TEXT("Attack dmg : %f"), DamageAmount);

	auto curSpawnDmgActor = Cast<AACT_DamgeText>(
		GetWorld()->SpawnActor<AActor>(_ACT_DmgText, spawnPos, spawnRot, spawnParams));

	curSpawnDmgActor->SetDamage(DamageAmount);
	curSpawnDmgActor->SetMyOwner(this);
	curSpawnDmgActor->UpdateDamage();

	_PS_HitEff->Activate(true);
	
	//hp바 표시
	VisibleHpBar();

	return DamageAmount;
}

void AUNIT_Character::VisibleHpBar()
{


}


void AUNIT_Character::DeadUnit()
{

	GetCapsuleComponent()->DestroyComponent(true);
	SoundPlay((int)ECharacterSounds::DEAD);
	
	_PSPR_MinimapIcon->SetSprite(nullptr);
}

void AUNIT_Character::SetOutline(bool on)
{
	GetMesh()->SetRenderCustomDepth(on);

	if(on)
		GetMesh()->SetCustomDepthStencilValue(2);
		
	else
		GetMesh()->SetCustomDepthStencilValue(0);
}

void AUNIT_Character::SetDebugText()
{

}

void AUNIT_Character::SetCreatureInfo()
{

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
