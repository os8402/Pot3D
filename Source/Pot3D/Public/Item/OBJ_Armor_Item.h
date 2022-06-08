// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/OBJ_Item.h"
#include "OBJ_Armor_Item.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UOBJ_Armor_Item : public UOBJ_Item
{
	GENERATED_BODY()

public:
	virtual void SetEquimentType()
	{
		int32 armorId = GetItemId() / 1000;

		_armorType = EItemArmorTypes(armorId);

	}

	EItemArmorTypes GetArmorType() {return _armorType;}


private:

	int32 _defence;
	EItemArmorTypes _armorType;
	


	
};
