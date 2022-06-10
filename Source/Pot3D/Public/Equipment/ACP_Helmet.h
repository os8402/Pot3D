// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/ACP_Equipment.h"
#include "ACP_Helmet.generated.h"

class UOBJ_Item;
class AUNIT_Character;

UCLASS()
class POT3D_API UACP_Helmet : public UACP_Equipment
{
	GENERATED_BODY()

public:

	UACP_Helmet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
