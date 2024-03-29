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
			_dropPosition = itemData->_dropPosition;
			_scale = itemData->_scale;
			
			UtilsLib::GetAssetDynamic<USoundWave>(&_vfxSoundWav , *itemData->_soundPath.ToString());
			SetEquimentType();

			//보너스 스탯 초기화
			for (int i = 0; i < (int32)EStatTypes::END; i++)
			{
				_bonusStats.Add(i,0);
			}

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
		int32 probability = 100 / (int32)EStatTypes::END - 1;
		int32 rand = FMath::RandRange(0, 101);

		for (int32 i = 0; i < (int32)EStatTypes::END; i++)
		{
			sum += probability;

			if (rand <= sum)
			{	
				int32 statRand = FMath::RandRange(1,10);
				_bonusStats[i] += statRand;
				SetFinalStat(i, statRand);
				break;
			}

		}
		cnt++;
	}

}

void UOBJ_Item::SetFinalStat(int32 id , int32 num)
{
	EStatTypes statType = EStatTypes(id);
	switch (statType)
	{
	case EStatTypes::STRENGH:
		_statData._strength += num;
		break;
	case EStatTypes::DEXTERITY:
		_statData._dexterity += num;
		break;
	case EStatTypes::INTELIGENCE:
		_statData._intelligence += num;
		break;
	case EStatTypes::RESILIENCE:
		_statData._resilience += num;
		break;
	case EStatTypes::LUCK:
		_statData._luck += num;
		break;
	case EStatTypes::HP:
		_statData._maxHp += num;
		break;
	case EStatTypes::MP:
		_statData._maxMp += num;
		break;
	default:
		break;
	}

}
