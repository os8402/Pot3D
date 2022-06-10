// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/ACP_Equipment.h"
#include "ACP_Boots.generated.h"

class UOBJ_Item;
class AUNIT_Character;

UCLASS()
class POT3D_API UACP_Boots : public UACP_Equipment
{
	GENERATED_BODY()

public:

	UACP_Boots();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
