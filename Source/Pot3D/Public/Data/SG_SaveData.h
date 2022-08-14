// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "GameDataTable.h"
#include "UI/WG_Slot.h"
#include "SG_SaveData.generated.h"


UCLASS()
class POT3D_API USG_SaveData : public USaveGame
{
	GENERATED_BODY()

public:
	USG_SaveData();

public:
	
	UPROPERTY()
	int32 _currentHp;
	UPROPERTY()
	int32 _currentMp;
	UPROPERTY()
	int32 _currentExp;
	UPROPERTY()
	int32 _gold;

	//내가 배운 스킬
	UPROPERTY()
	TMap<int32, int32> _acquireSkills;

	UPROPERTY()
	TMap<int32, int32> _mainbarSlots;

	UPROPERTY()
	TMap<int32, int32> _inventorySlots;

	UPROPERTY()
	int32 _equipmentWeapon;
	UPROPERTY()
	TArray<int32> _equipmentArmors;

};
