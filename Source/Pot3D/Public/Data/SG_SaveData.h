// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "GameDataTable.h"
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
	UPROPERTY()
	FStatData _statData;




};
