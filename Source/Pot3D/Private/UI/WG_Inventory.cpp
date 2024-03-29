﻿#include "UI/WG_Inventory.h"
#include "Item/OBJ_Item.h"
#include "Item/OBJ_Weapon_Item.h"
#include "Item/OBJ_Armor_Item.h"
#include "Item/OBJ_Consumable_Item.h"
#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_Equipment_ItemSlot.h"
#include "UI/WG_Tooltip_Item.h"
#include "UI/WG_Status.h"
#include "Manager/GI_GmInst.h"
#include "Manager/PS_PlayerState.h"

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

	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);
	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	UWrapBox* slotBox = WidgetTree->FindWidget<UWrapBox>("_WBOX_SlotBox");

	if (slotBox && IsValid(_itemSlotClass))
	{
		TMap<int32 ,int32> savedInventorySlots = ps->GetInventorySlots();

		for (int i = 0; i < _itemMaxSlotNum; i++)
		{

			UWG_Inventory_ItemSlot* itemSlot = CreateWidget<UWG_Inventory_ItemSlot>(this, _itemSlotClass);
			slotBox->AddChild(itemSlot);

			itemSlot->SetInventory(this);
			itemSlot->SetSlotNum(i);

			_inventoryData.Add(i, itemSlot);
			// Get SAVE DATA

			if (savedInventorySlots[i] != -1)
			{
				UOBJ_Item* copyItem = CreateCopyItem(savedInventorySlots[i]);
				
				itemSlot->SetItem(copyItem);
			}

			itemSlot->SetToolTip(_WBP_Tooltip_Item);

		}
	}

	int32 savedWeaponId = ps->GetEquipmentWeapon();
	UOBJ_Item* weaponItem = CreateCopyItem(savedWeaponId);

	if(weaponItem)
		EquipItem(weaponItem);

	_WBP_Equipment_Weapon->SetToolTip(_WBP_Tooltip_Item);
	_WBP_Equipment_Weapon->SetInventory(this);

	_equipment_ArmorLists.Add((int32)EItemArmorTypes::HELMET, _WBP_Equipment_Helmet);
	_equipment_ArmorLists.Add((int32)EItemArmorTypes::ARMOR, _WBP_Equipment_Armor);
	_equipment_ArmorLists.Add((int32)EItemArmorTypes::PANTS, _WBP_Equipment_Pants);
	_equipment_ArmorLists.Add((int32)EItemArmorTypes::BOOTS, _WBP_Equipment_Boots);

	int32 cnt = 0;

	for (auto& armor : _equipment_ArmorLists)
	{
		armor.Value->SetToolTip(_WBP_Tooltip_Item);
		armor.Value->SetInventory(this);

		int32 savedArmorId = ps->GetEquipmentArmor(cnt++);

		UOBJ_Item* armorItem = CreateCopyItem(savedArmorId);
		if (armorItem)
			EquipItem(armorItem);

	}

	_WBP_Tooltip_Item->SetVisibility(ESlateVisibility::Hidden);

	RefreshInventory();

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

	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);

	EItemTypes itemtype = newItem->GetItemType();

	if (itemtype == EItemTypes::GOLD || itemtype == EItemTypes::JEWEL)
	{
		// TODO : 재화 처리
		if (itemtype == EItemTypes::GOLD)
		{

			if (ps)
			{
				ps->SetGold(newItem->GetCount());

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

		//TODO : Save

		if (ps)
		{
			ps->SetInventorySlot(emptySlot , newItem->GetItemId());
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

	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);

	if(ps)
		ps->SetInventorySlot(slot, -1);

	RefreshInventory();
}

void UWG_Inventory::UseItem(int32 slot)
{
	//_inventoryData[slot]->_count -= 1;
	RefreshInventory();
}

void UWG_Inventory::EquipItem(int32 slot)
{
	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);


	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Equip Item"));

	if (_currentOwner.IsValid())
	{
		UOBJ_Item* item = _inventoryData[slot]->GetItem();

		if(item == nullptr)
			return;

		EItemTypes itemType = item->GetItemType();

		if (itemType == EItemTypes::WEAPON)
		{
			//TODO : 장비 해제 작업
			if (_WBP_Equipment_Weapon->GetItem())
			{
				UOBJ_Item* equippedItem = _WBP_Equipment_Weapon->GetItem();
				UnEquipItem(equippedItem);

			}

			_currentOwner->GetWeapon()->EquipItem(item);
			//TODO : Equipment Slot
			_WBP_Equipment_Weapon->SetItem(item);

			if(ps)
				ps->SetEquipmentWeapon(item->GetItemId());
		}

		else
		{
			UOBJ_Armor_Item* armorItem = Cast<UOBJ_Armor_Item>(item);

			EItemArmorTypes armorType = armorItem->GetArmorType();

			auto equipmentSlot = _equipment_ArmorLists[(int32)armorType];

			//TODO : 장비 해제 작업
			if (equipmentSlot->GetItem())
			{
				UOBJ_Item* equippedItem = equipmentSlot->GetItem();
				UnEquipItem(equippedItem);
	
			}
			
			_currentOwner->GetArmorList()[(int32)armorType]->EquipItem(item);
			//TODO : Equipment Slot
			equipmentSlot->SetItem(item);

			if(ps)
				ps->SetEquipmentArmor((int32)armorType, item->GetItemId());

		}

		//슬롯 제거 작업

		RemoveItem(slot);
		RefreshInventory();
	}
}



void UWG_Inventory::EquipItem(UOBJ_Item* item)
{
	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);

	auto player = Cast<AUNIT_Player>(pc->GetCharacter());


	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Equip Item"));

	if (player)
	{

		if (item == nullptr)
			return;

		EItemTypes itemType = item->GetItemType();

		if (itemType == EItemTypes::WEAPON)
		{
			player->GetWeapon()->EquipItem(item);
			//TODO : Equipment Slot
			_WBP_Equipment_Weapon->SetItem(item);

		}

		else
		{
			UOBJ_Armor_Item* armorItem = Cast<UOBJ_Armor_Item>(item);

			EItemArmorTypes armorType = armorItem->GetArmorType();

			auto equipmentSlot = _equipment_ArmorLists[(int32)armorType];

			player->GetArmorList()[(int32)armorType]->EquipItem(item);
			//TODO : Equipment Slot
			equipmentSlot->SetItem(item);

		}

		RefreshInventory();
	}
}

void UWG_Inventory::UnEquipItem(UOBJ_Item* equippedItem, bool bAdd)
{
	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("UnEquip Item"));

	if(equippedItem == nullptr)
		return;


	EItemTypes itemType = equippedItem->GetItemType();

	if (itemType == EItemTypes::WEAPON)
	{
		//TODO : UnEquipment Character
		//_currentOwner->GetWeapon()->SetEquipItem(item);
		//TODO : Equipment Slot

		_WBP_Equipment_Weapon->SetItem(nullptr);
		_currentOwner->GetWeapon()->UnEquipItem();

		if(ps)
			ps->SetEquipmentWeapon(-1);

	}

	else
	{
		UOBJ_Armor_Item* armorItem = Cast<UOBJ_Armor_Item>(equippedItem);

		EItemArmorTypes armorType = armorItem->GetArmorType();
		//TODO : UnEquipment Character
		//_currentOwner->GetArmorList()[(int32)armorType]->SetEquipItem(item);
		//TODO : Equipment Slot
		_equipment_ArmorLists[(int32)armorType]->SetItem(nullptr);
		_currentOwner->GetArmorList()[(int32)armorType]->UnEquipItem();
	
		if (ps)
			ps->SetEquipmentArmor((int32)armorType , -1);

	}

	if(bAdd)
		AddItem(equippedItem);

	RefreshInventory();

}

void UWG_Inventory::ChangeItemSlot(int32 prev, int32 next)
{
	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);

	UOBJ_Item* prevItem = _inventoryData[prev]->GetItem();
	UOBJ_Item* nextItem = _inventoryData[next]->GetItem();

	_inventoryData[next]->SetItem(prevItem);
	_inventoryData[prev]->SetItem(nextItem);

	if(ps)
		ps->ChangeInventorySlot(prev , next);

	RefreshInventory();
}

void UWG_Inventory::RefreshInventory()
{
	//Gold 
	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);

	if (ps)
	{
		int32 gold = ps->GetGold();
		_TB_Gold->SetText(FText::FromString(FString::FromInt(gold)));

	}

	//Item Info Setting
	
	for (int32 i = 0; i < _itemMaxSlotNum; i++)
	{
		if(_inventoryData[i] != nullptr)
			_inventoryData[i]->RefreshUI();

	}

	//Status Setting

	if (_currentOwner.IsValid())
	{
		_WBP_Status->RefreshStat(_currentOwner.Get()->GetStatComp());
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

UOBJ_Item* UWG_Inventory::CreateCopyItem(int32 itemId)
{
	if(itemId == -1)
		return nullptr;

	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);
	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	UOBJ_Item* newItem = NewObject<UOBJ_Item>(UOBJ_Item::StaticClass());
	FItemData* itemData = gmInst->GetTableData<FItemData>(ETableDatas::ITEM, itemId);

	if (itemData)
	{
		EItemTypes itemType = itemData->_itemType;
		if (itemType == EItemTypes::WEAPON)
		{
			auto weaponItemClass = UOBJ_Weapon_Item::StaticClass();
			auto weaponItem = NewObject<UOBJ_Weapon_Item>(weaponItemClass);
			newItem = weaponItem;
		}
		else if (itemType == EItemTypes::ARMOR)
		{
			auto armorItemClass = UOBJ_Armor_Item::StaticClass();
			auto armorItem = NewObject<UOBJ_Armor_Item>(armorItemClass);
			newItem = armorItem;
		}
		else if (itemType == EItemTypes::CONSUMABLE)
		{
			auto consumableItemClass = UOBJ_Consumable_Item::StaticClass();
			auto consumableItem = NewObject<UOBJ_Consumable_Item>(consumableItemClass);
			newItem = consumableItem;
		}

	}

	newItem->SetItemInfo(gmInst, itemId, 1);

	return newItem;
}


void UWG_Inventory::SetItemTooltipHovered(UOBJ_Item* item)
{

	if (item == nullptr)
	{
		_WBP_Tooltip_Item->SetVisibility(ESlateVisibility::Hidden);

		if (_hoveredItem.IsValid())
			_hoveredItem.Reset();

		return;
	}

	if(_hoveredItem == item)
		return;

	_hoveredItem = item;

	_WBP_Tooltip_Item->SetVisibility(ESlateVisibility::Visible);
	_WBP_Tooltip_Item->SetRenderTranslation(FVector2D(-500, -100));

	FString goldStr = FString::Printf(TEXT("Item Info :  %s"), *item->GetItemName().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, goldStr);

	//TODO : 툴팁 정보 갱신

	_WBP_Tooltip_Item->RefreshUI(item);
}


