// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/OBJ_Item.h"
#include "OBJ_Jewel_Item.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UOBJ_Jewel_Item : public UOBJ_Item
{
	GENERATED_BODY()

public:
	UOBJ_Jewel_Item()
	{
		SetItemType(EItemTypes::JEWEL);
	}
	
};
