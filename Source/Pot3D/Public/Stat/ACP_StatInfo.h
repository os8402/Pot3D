// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UEnumHeader.h"
#include "ACP_StatInfo.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged)
DECLARE_MULTICAST_DELEGATE(FOnMpChanged)
DECLARE_MULTICAST_DELEGATE(FOnUnitDied)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_StatInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_StatInfo();

protected:

	virtual void InitializeComponent() override;

public:
	void OnAttacked(int32 dmg);


public:

	void SetCharacterId(int32 id);
	void SetHp(int32 newHp);
	void SetMp(int32 newMp);
	void SetExp(int32 exp);

	int32 GetCharacterId() { return _chrId; }
	FString GetChracterName() { return _chrName;}
	int32 GetHp() { return _hp; }
	int32 GetMaxHp() { return _maxHp; }
	float GetHpRatio() { return  _hp / (float)_maxHp; }
	int32 GetLevel() { return _level; }
	int32 GetJob() { return _job; }

	int32 GetMinAttack() { return _minAtk; }
	int32 GetMaxAttack() { return _maxAtk; }
	int32 GetDefense() { return _defence; }
	int32 GetResilience() { return _resilience; }
	int32 GetStrength() { return _strength; }
	int32 GetDexterity() { return _dexterity; }
	int32 GetIntelligence() { return _intelligence; }
	int32 GetLuck() { return _luck; }

	FOnHpChanged& GetOnHpChanged() { return _onHpChanged; }
	FOnUnitDied& GetOnUnitDied() { return _onUnitDied; }

private:


	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _chrId;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	FString _chrName;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _level;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _job;

	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _hp;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _mp;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxHp;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxMp;

	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _minAtk;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxAtk;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _defence;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _resilience;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _strength;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _dexterity;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _intelligence;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _luck;

	FOnHpChanged _onHpChanged;
	FOnHpChanged _onMpChanged;
	FOnUnitDied _onUnitDied;

};
