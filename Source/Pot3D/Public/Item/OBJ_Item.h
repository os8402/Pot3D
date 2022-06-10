// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UEnumHeader.h"
#include "Manager/GI_GmInst.h"
#include "OBJ_Item.generated.h"


UCLASS()
class POT3D_API UOBJ_Item : public UObject
{
	GENERATED_BODY()

public:



	int32 GetItemId() {return _id;}
	FText GetItemName() {return _name;}
	FName GetMeshPath() {return _meshPath;}
	FName GetTexturePath() {return _iconPath;}
	int32 GetCount() {return _count;}
	bool GetIsConsumable(){return _isConsumable;}
	ERarity GetRarity(){return _rarity;}
	FStatData GetStatData() {return _statData;}
	EItemTypes GetItemType(){return _itemType;}

	TMap<int32, int32> GetBonusStats() {return _bonusStats;}

	virtual void SetEquimentType();


public:
	bool SetItemInfo(class UGI_GmInst* gmInst , int32 id, int32 count);
	void SetRandomBonusStat();

	//���ʽ� ���ȱ��� ��ģ �� ����
	void SetFinalStat(int32 id, int32 num);

private:

	UPROPERTY()
	class UGI_GmInst* _gmInst;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 _id;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FText _name;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName _meshPath;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName _iconPath;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 _count;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	bool _isConsumable = false;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	ERarity _rarity;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemTypes _itemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FStatData _statData;


	UPROPERTY()
	TMap<int32, int32> _bonusStats;
	
};
