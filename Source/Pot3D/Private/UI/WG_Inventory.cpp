// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory.h"
#include "Item/OBJ_Item.h"
#include "Manager/GI_GmInst.h"

#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>


bool UWG_Inventory::AddItem(UOBJ_Item* newItem)
{
	if (newItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add Item Failed"));
		return false;
	}


	int32 emptySlot = GetEmptySlot();


	if (emptySlot == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Is Full"));
		return false;

	}

	EItemTypes itemtype = newItem->GetItemType();

	if (itemtype == EItemTypes::GOLD || itemtype == EItemTypes::JEWEL)
	{
		// TODO : 犁拳 贸府
		if (itemtype == EItemTypes::GOLD)
		{
			auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (gmInst)
			{
				gmInst->SetGold(newItem->GetCount());
			}
		}
	}

	else
	{
		_inventoryData.Add(emptySlot, newItem);
	}



	RefreshInventory();

	return true;

}

void UWG_Inventory::RemoveItem(int32 slot)
{
	_inventoryData.Remove(slot);
	RefreshInventory();
}

void UWG_Inventory::UseItem(int32 slot)
{
	//_inventoryData[slot]->_count -= 1;
	RefreshInventory();
}

void UWG_Inventory::RefreshInventory()
{
	//Gold 
	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gmInst)
	{
		int32 gold = gmInst->GetGold();
		_TB_Gold->SetText(FText::FromString(FString::FromInt(gold)));
	}

}

int32 UWG_Inventory::GetEmptySlot()
{
	int32 emptySlot = -1;

	//后 浇吩 ずつ农
	for (int32 i = 0; i < _itemMaxSlot; i++)
	{
		UOBJ_Item* const* isItem = _inventoryData.Find(i);

		if (isItem == nullptr)
		{
			return i;
		}
	}

	return emptySlot;
}
