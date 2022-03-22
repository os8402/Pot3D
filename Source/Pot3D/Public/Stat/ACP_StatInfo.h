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
	virtual void SetLevel(int32 level);
	void SetHp(int32 newHp);
	void SetMp(int32 newMp);
	

	void SetExp(int32 exp);


	int32 GetHp() { return _hp; }
	int32 GetMaxHp() { return _maxHp; }
	float GetHpRatio() { return  _hp / (float)_maxHp; }
	int32 GetLevel() { return _level; }
	int32 GetAttack() { return _attack; }

	FOnHpChanged& GetOnHpChanged() { return _onHpChanged; }
	FOnUnitDied& GetOnUnitDied() { return _onUnitDied; }


	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _level;

	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _hp;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _mp;

	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxHp;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxMp;
	UPROPERTY(EditAnyWhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _attack;

	FOnHpChanged _onHpChanged;
	FOnHpChanged _onMpChanged;
	FOnUnitDied _onUnitDied;

};
