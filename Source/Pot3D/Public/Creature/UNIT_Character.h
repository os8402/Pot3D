// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UEnumHeader.h"
#include "UtilsLib.h"
#include "UNIT_Character.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnded)
UCLASS()
class POT3D_API AUNIT_Character : public ACharacter
{
	GENERATED_BODY()


public:
	
	AUNIT_Character();

protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void TickRecovery(float DeltaTime);

public:	

	virtual void Tick(float DeltaTime) override;


public:

	//1.플컨에서 공격명령
	void AttackEnemy();
	//2.애니 몽타주 
	virtual void AttackAnimCheck();
	//3.공격 가능한 지 [애니 몽타주 안에 들어있음] 
	bool CanAttack();

	virtual void SkillAnimCheck();


	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInteruppted);
	UFUNCTION()
	void OnSkillMontageEnded(UAnimMontage* montage, bool bInteruppted);


	virtual void UseActiveSKill(FName skillName);


	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void OnHitFlag(float DeltaTime);

	virtual void VisibleHpBar();
	virtual void DeadUnit();

	void SetOutline(bool on = true);



public:

	void SetConnectedId(int32 index) { _connectedId = index; }
	int32 GetConnectedId() { return _connectedId; }

	int32 GetCharacterId() { return _chrId; }
	
	class UUNIT_Anim* GetUnitAnim() { return _unitAnim; }

	TWeakObjectPtr<class AUNIT_Character>& GetTargetEnemy() { return _targetEnemy; }
	void SetTargetEnemy(class AUNIT_Character* target) { _targetEnemy = target; }
	bool IsAttacking() { return _bAttacking; }

	FOnAttackEnded& GetOnAttackEnded() { return _onAttackEnded; }
	class UACP_StatInfo* GetStatComp() { return _ACP_Stat; }
	class UACP_SKillInfo* GetSkillComp() { return _ACP_Skill; }

	class UACP_Weapon* GetWeapon() { return _ACP_Weapon; }



public:

	//확장여지잇음 
	void SetUnitStates(EUnitStates state);
	EUnitStates GetUnitStates() { return _UnitStates; }


protected:

	int32 _connectedId = 0;
	UPROPERTY(EditAnywhere, Category = "ID")
	int32 _chrId = 0;


protected:

	//MESH
	class UUNIT_Anim* _unitAnim;

protected:

	//ATTACK 
	// 플컨에서 잡고 있는 타겟 [ 몬스터 ]
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<class AUNIT_Character> _targetEnemy;

	bool _bAttacking = 0;
	FOnAttackEnded _onAttackEnded;
	int32 _attackIndex = 0;


protected:

	FTimerHandle _deadHandle;
//
protected:

	//스탯 

	UPROPERTY(VisibleAnywhere,  Category="Stat")
	class UACP_StatInfo* _ACP_Stat;

	float _tickRecoveryTime = 0.f;

protected:

// 스킬
	
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	class UACP_SKillInfo* _ACP_Skill;

protected:
	
	UPROPERTY(VisibleAnywhere , Category="UI")
	TSubclassOf<AActor> _ACT_DmgText;

	UPROPERTY(VisibleAnywhere, Category="UI")
	class AACT_DamgeText* _currentDmgActor;

protected:
	//EQUIPMENT 
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class UACP_Weapon* _ACP_Weapon;

protected:
	//ENUM
	UPROPERTY(VisibleAnywhere, Category="Pawn")
	EUnitStates _UnitStates; 
	//ENUM
	UPROPERTY(EditAnywhere, Category = "Pawn")
	EUnitJobs _unitJobs;

private :

	//HIT
	UPROPERTY(VisibleAnywhere, Category="Effect")
	class UParticleSystemComponent* _PS_HitEff;

	UPROPERTY(VisibleAnywhere, Category="Effect")
	TArray<UMaterialInstanceDynamic*> _MID_meshs;
	
	bool _bHitFlag = false;
	float _hitFlagGauge = 0.f;
	float _hitSpeed = 2.f;



};
