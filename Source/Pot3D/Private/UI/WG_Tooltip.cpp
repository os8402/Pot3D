// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Tooltip.h"
#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_TitleBar.h"
#include "Item/OBJ_Item.h"

#include <Components/Image.h>
#include <COmponents/TextBlock.h>

void UWG_Tooltip::RefreshUI(UOBJ_Item* item)
{
	_WBP_TitleBar->SetTitle(item->GetItemName());
	_WBP_Inventory_ItemSlot->SetItem(item);


	Localization(item);


}

void UWG_Tooltip::Localization(UOBJ_Item* item)
{
	//TODO : 문서로 불러와야 하지만.. 나중에..

	int32 itemId = item->GetItemId();
	ERarity rarity = item->GetRarity();
	EItemTypes itemType = item->GetItemType();


	FString strRarity; 
	FString strItemType;

	switch (rarity)
	{
	case ERarity::NORMAL:
		strRarity = FString(TEXT("일반"));
		break;
	case ERarity::RARE:
		strRarity = FString(TEXT("레어"));
		break;
	case ERarity::UNIQUE:
		strRarity = FString(TEXT("영웅"));
		break;
	case ERarity::LEGENDARY:
		strRarity = FString(TEXT("전설"));
		break;

	default:
		break;
	}



	switch (itemType)
	{

	case EItemTypes::WEAPON :
		strItemType = FString(TEXT("무기"));
		break;
	case EItemTypes::ARMOR:
		strItemType = FString(TEXT("방어구"));
		break;
	case EItemTypes::CONSUMABLE:
		strItemType = FString(TEXT("소모품"));
		break;
	case EItemTypes::JEWEL:
		strItemType = FString(TEXT("보석"));
		break;
	case EItemTypes::GOLD:
		strItemType = FString(TEXT("금화"));
		break;

	default:
		break;
	}


	_TB_Grade->SetText(FText::FromString(strRarity));
	_TB_ItemType->SetText(FText::FromString(strItemType));

	

}
