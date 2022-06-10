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
	// Sets default values for this character's properties
	AUNIT_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	


public:

	void AttackEnemy();
	virtual void AttackCheck();
	void SoundPlay(int32 index);
	bool CanAttack();


	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInteruppted);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void VisibleHpBar();
	virtual void DeadUnit();

	void SetOutline(bool on = true);

	void SetDebugText();


public:

	void SetConnectedId(int32 index) { _connectedId = index; }
	int32 GetConnectedId() { return _connectedId; }

	int32 GetCharacterId() { return _chrId; }
	void SetCreatureInfo();
	

	class UUNIT_Anim* GetUnitAnim() { return _unitAnim; }


	TWeakObjectPtr<class AUNIT_Character>& GetTargetEnemy() { return _targetEnemy; }
	void SetTargetEnemy(class AUNIT_Character* target) { _targetEnemy = target; }

	bool IsAttacking() { return _bAttacking; }

	FOnAttackEnded& GetOnAttackEnded() { return _onAttackEnded; }
	class UACP_StatInfo* GetStatComp() { return _ACP_Stat; }


public:

	//»Æ¿Âø©¡ˆ¿’¿Ω 
	void SetUnitStates(EUnitStates state);
	EUnitStates GetUnitStates() { return _UnitStates; }

	void SetUnitTypes(EUnitTypes type) { _UnitTypes = type; }
	EUnitTypes GetUnitTypes() { return _UnitTypes; }

	void SetCharJobs(EUnitJobs type) { _UnitJobs = type; }
	EUnitJobs GetCharJobs() { return _UnitJobs; }

	class UAudioComponent* GetAudioComp() { return _Audio_Comp; }
	class UACP_Weapon* GetWeapon() { return _ACP_Weapon; }
	class UACP_Armor* GetArmor() { return _ACP_Armor; }


private:

	int32 _connectedId = 0;
	UPROPERTY(EditAnywhere, Category = "ID")
	int32 _chrId = 0;


protected:

	//MESH
	class UUNIT_Anim* _unitAnim;

protected:

	//ATTACK 

	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<class AUNIT_Character> _targetEnemy;

	bool _bAttacking = 0;

	FOnAttackEnded _onAttackEnded;

protected:

	FTimerHandle _deadHandle;
//
protected:

	//Ω∫≈» 

	UPROPERTY(VisibleAnywhere,  Category="Stat")
	class UACP_StatInfo* _ACP_Stat;


protected:
	
	UPROPERTY(VisibleAnywhere , Category="UI")
	TSubclassOf<class AActor> _ACT_DmgText;

	UPROPERTY(VisibleAnywhere, Category="UI")
	class AACT_DamgeText* _currentDmgActor;


protected:
	
	
	UPROPERTY(EditAnywhere, Category = "UI")
	float _hpZPos = 250.f;

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector2D _hpDrawSize = {200.f , 70.f};

	UPROPERTY(VisibleAnywhere , Category="UI")
	class UWidgetComponent* _WG_HpBar;

	FTimerHandle _hpBarTimer;


private :
	//ENUM
	UPROPERTY(VisibleAnywhere, Category="Pawn")
	EUnitStates _UnitStates; 

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	EUnitTypes _UnitTypes;

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	EUnitJobs _UnitJobs;

private :

	UPROPERTY(VisibleAnywhere, Category="Effect")
	class UParticleSystemComponent* _PS_HitEff;


protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* _SPR_MinimapSpring;

	UPROPERTY(VisibleAnywhere)
	class USceneCaptureComponent2D* _SC_MinimapCam;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* _PSPR_MinimapIcon;

private: 
	

	UPROPERTY(EditDefaultsOnly, Category="Audio")
	TArray<class USoundCue*> _SOUND_CHAR_Lists;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	class UAudioComponent* _Audio_Comp;

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class UACP_Weapon* _ACP_Weapon;
	UPROPERTY(VisibleAnywhere, Category = "Armor")
	class UACP_Armor* _ACP_Armor;


};
