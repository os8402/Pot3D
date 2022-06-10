// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/ACP_Equipment.h"
#include "ACP_Armor.generated.h"

class UOBJ_Item;
class AUNIT_Character;

UCLASS()
class POT3D_API UACP_Armor : public UACP_Equipment
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_Armor();

	void SetArmor(UOBJ_Item* item);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
