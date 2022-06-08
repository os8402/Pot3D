// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/OBJ_Item.h"



void UOBJ_Item::SetEquimentType()
{

}

bool UOBJ_Item::SetItemInfo(class UGI_GmInst* gmInst, int32 id, int32 count)
{
	_gmInst = gmInst;
	bool flag = false;

	if (_gmInst)
	{
		auto itemData = _gmInst->GetTableData<FItemData>(ETableDatas::ITEM, id);

		if (itemData)
		{
			_id = itemData->_id;
			_name = itemData->_name;
			_meshPath = itemData->_meshPath;
			_iconPath = itemData->_iconPath;
			_count = count;
			_isConsumable = itemData->_isConsumable;
			_rarity = itemData->_rarity;
			_itemType = itemData->_itemType;
			_statData = itemData->_statData;

			SetEquimentType();
			SetRandomBonusStat();

			flag = true;
		}
	}

	return flag;
}

void UOBJ_Item::SetRandomBonusStat()
{
	
	if(_itemType == EItemTypes::GOLD || _itemType == EItemTypes::JEWEL || _itemType == EItemTypes::CONSUMABLE )
		return;

	int cnt = 0 ;
	int statBonusNum = (int32)_rarity + 1;


	while (cnt <  statBonusNum)
	{
		int32 sum = 0 ;
		int32 probability = 100 / (int32)EStatTypes::END;
		int32 rand = FMath::RandRange(0, 101);

		for (int32 i = 0; i < (int32)EStatTypes::END; i++)
		{
			sum += probability;

			if (rand <= sum)
			{	
				int32 statRand = FMath::RandRange(1,10);
				_bonusStats.Add(i , statRand);
				break;
			}

		}
		cnt++;
	}

}
