// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UNIT_Character.h"
#include "UNIT_Monster.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API AUNIT_Monster : public AUNIT_Character
{
	GENERATED_BODY()
	
public:
	AUNIT_Monster();
	virtual void PostInitializeComponents() override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual void DeadUnit() override;

};
