// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/OBJ_Item.h"
#include "OBJ_Weapon_Item.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UOBJ_Weapon_Item : public UOBJ_Item
{
	GENERATED_BODY()

public:

	virtual void SetEquimentType()
	{
		int weaponId = GetItemId() / 100;

		_weaponType = EItemWeaponTypes(weaponId);

	}

	EItemWeaponTypes GetWeaponType() {return _weaponType;}
	

private:

	int32 _minDamage;
	int32 _maxDamage;

	int32 _attackSpeed;

	EItemWeaponTypes _weaponType;
	

};
