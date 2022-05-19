// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/OBJ_Item.h"
#include "Manager/GI_GmInst.h"

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
			_count = count;
			_isConsumable = itemData->_isConsumable;
			_rarity = itemData->_rarity;


			flag = true;
		}


	}

	return flag;
}
