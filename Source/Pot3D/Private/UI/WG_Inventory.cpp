// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory.h"
#include "Item/OBJ_Item.h"
#include "Item/OBJ_Weapon_Item.h"
#include "Item/OBJ_Armor_Item.h"
#include "Item/OBJ_Consumable_Item.h"
#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_Equipment_ItemSlot.h"
#include "UI/WG_Tooltip.h"
#include "Manager/GI_GmInst.h"

#include "Creature/UNIT_Player.h"
#include "Equipment/ACP_Weapon.h"
#include "Equipment/ACP_Armor.h"

#include <Components/WidgetComponent.h>
#include <Components/WrapBox.h>
#include <COmponents/Button.h>
#include <Blueprint/WidgetTree.h>

#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>


void UWG_Inventory::NativePreConstruct()
{
	Super::NativePreConstruct();

	UWrapBox* slotBox = WidgetTree->FindWidget<UWrapBox>("_WBOX_SlotBox");

	if (slotBox && IsValid(_itemSlotClass))
	{
		for (int i = 0; i < _itemMaxSlotNum; i++)
		{
			UWG_Inventory_ItemSlot* itemSlot = CreateWidget<UWG_Inventory_ItemSlot>(this, _itemSlotClass);
			slotBox->AddChild(itemSlot);

			itemSlot->SetInventory(this);
			itemSlot->SetSlotNum(i);

			_inventoryData.Add(i, itemSlot);
		
			itemSlot->SetToolTip(_WBP_Tooltip);
			itemSlot->ToolTipWidget->SetRenderTranslation(FVector2D(-500,0));

		}

	}

	_WBP_Equipment_Weapon->SetToolTip(_WBP_Tooltip);
	_WBP_Equipment_Weapon->ToolTipWidget->SetRenderTranslation(FVector2D(-500, 0));

	_equipment_ArmorLists.Add((int32)EItemArmorTypes::HELMET, _WBP_Equipment_Helmet);
	_equipment_ArmorLists.Add((int32)EItemArmorTypes::ARMOR, _WBP_Equipment_Armor);
	_equipment_ArmorLists.Add((int32)EItemArmorTypes::PANTS, _WBP_Equipment_Pants);
	_equipment_ArmorLists.Add((int32)EItemArmorTypes::BOOTS, _WBP_Equipment_Boots);

	for (auto& armor : _equipment_ArmorLists)
	{
		armor.Value->SetToolTip(_WBP_Tooltip);
		armor.Value->ToolTipWidget->SetRenderTranslation(FVector2D(-500, 0));
	}
}



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
		// TODO : 재화 처리
		if (itemtype == EItemTypes::GOLD)
		{
			auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (gmInst)
			{
				gmInst->SetGold(newItem->GetCount());

				FString goldStr = FString::Printf(TEXT("Add Gold :  %d"), newItem->GetCount());
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, goldStr);
			}
		}
	}

	else
	{

		if (itemtype == EItemTypes::WEAPON)
		{
			UOBJ_Weapon_Item* weaponItem = Cast<UOBJ_Weapon_Item>(newItem);	
			_inventoryData[emptySlot]->SetItem(weaponItem);
		}
		
		else if (itemtype == EItemTypes::ARMOR)
		{
			UOBJ_Armor_Item* armorItem = Cast<UOBJ_Armor_Item>(newItem);
			_inventoryData[emptySlot]->SetItem(armorItem);
		}
		
		else if (itemtype == EItemTypes::CONSUMABLE)
		{
			UOBJ_Consumable_Item* consumableItem = Cast<UOBJ_Consumable_Item>(newItem);
			_inventoryData[emptySlot]->SetItem(consumableItem);
		}
			
		FString str = FString::Printf(TEXT("Get Item :  %s"), *newItem->GetItemName().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);
	}



	RefreshInventory();

	return true;

}

void UWG_Inventory::RemoveItem(int32 slot)
{
	_inventoryData[slot]->SetItem(nullptr);

	RefreshInventory();
}

void UWG_Inventory::UseItem(int32 slot)
{
	//_inventoryData[slot]->_count -= 1;
	RefreshInventory();
}

void UWG_Inventory::EquipItem(int32 slot)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Equip Item"));

	if (_currentOwner.IsValid())
	{
		UOBJ_Item* item = _inventoryData[slot]->GetItem();

		if(item == nullptr)
			return;

		EItemTypes itemType = item->GetItemType();

		if (itemType == EItemTypes::WEAPON)
		{
			_currentOwner->GetWeapon()->SetEquipItem(item);
			//TODO : Equipment Slot
			_WBP_Equipment_Weapon->SetItem(item);
		}

		else
		{
			UOBJ_Armor_Item* armorItem = Cast<UOBJ_Armor_Item>(item);

			EItemArmorTypes armorType = armorItem->GetArmorType();
			_currentOwner->GetArmorList()[(int32)armorType]->SetEquipItem(item);
			//TODO : Equipment Slot
			_equipment_ArmorLists[(int32)armorType]->SetItem(item);

		}

		//슬롯 제거 작업

		RemoveItem(slot);
		RefreshInventory();
	}
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

	//Item Info Setting
	
	for (int32 i = 0; i < _itemMaxSlotNum; i++)
	{
		if(_inventoryData[i] != nullptr)
			_inventoryData[i]->RefreshUI();

	}
}

int32 UWG_Inventory::GetEmptySlot()
{
	int32 emptySlot = -1;

	//빈 슬롯 ㅊㅔ크
	for (int32 i = 0; i < _itemMaxSlotNum; i++)
	{
		UOBJ_Item* isItem = _inventoryData[i]->GetItem();

		if (isItem == nullptr)
		{
			return i;
		}
	}

	return emptySlot;
}

void UWG_Inventory::SetItemTooltipHovered(UOBJ_Item* item)
{

	if (item == nullptr)
	{
		_WBP_Tooltip->SetVisibility(ESlateVisibility::Hidden);

		if (_hoveredItem.IsValid())
			_hoveredItem.Reset();

		return;
	}

	if(_hoveredItem == item)
		return;

	_hoveredItem = item;

	_WBP_Tooltip->SetVisibility(ESlateVisibility::Visible);

	FString goldStr = FString::Printf(TEXT("Item Info :  %s"), *item->GetItemName().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, goldStr);

	//TODO : 툴팁 정보 갱신

	_WBP_Tooltip->RefreshUI(item);
}
