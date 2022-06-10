// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_Inventory.h"

#include "Item/OBJ_Item.h"
#include "Item/OBJ_Armor_Item.h"

#include "Creature/UNIT_Player.h"

#include "Equipment/ACP_Weapon.h"
#include "Equipment/ACP_Armor.h"

#include <Components/WrapBox.h>
#include <Blueprint/WidgetTree.h>
#include <Components/Image.h>
#include <COmponents/Button.h>


void UWG_Inventory_ItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	RefreshUI();

}




void UWG_Inventory_ItemSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_BTN_Slot->IsHovered() && _inventory.IsValid())
	{
		
		_inventory->SetItemTooltipHovered(_item);

	}

}

void UWG_Inventory_ItemSlot::RefreshUI()
{
	if (_item == nullptr)
	{
		_IMG_Icon->SetColorAndOpacity(FLinearColor::Transparent);
		return;
	}

	_IMG_Icon->SetColorAndOpacity(FLinearColor::White);
	_IMG_Icon->SetBrushFromTexture(_texture);

}

void UWG_Inventory_ItemSlot::SetItem(UOBJ_Item* item)
{
	if(item == nullptr)
		return;
	
	_item = item;

	//TODO : Texture Set

	UTexture2D* newTexture = Cast<UTexture2D>(
		StaticLoadObject(UTexture2D::StaticClass(), nullptr , *item->GetTexturePath().ToString()));

	if (newTexture != nullptr)
		_texture = newTexture;
	
	RefreshUI();

}

void UWG_Inventory_ItemSlot::EquipItem()
{
	
	if (_inventory.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Equip Item"));
		AUNIT_Player* player = _inventory->GetCurrentOwner();

		if (player)
		{
			EItemTypes itemType = _item->GetItemType();

			if (itemType == EItemTypes::WEAPON)
			{
				player->GetWeapon()->SetEquipItem(_item);
			}
		
			else
			{
				UOBJ_Armor_Item* armorItem = Cast<UOBJ_Armor_Item>(_item);
				
				EItemArmorTypes armorType = armorItem->GetArmorType();
				player->GetArmorList()[(int32)armorType]->SetEquipItem(_item);
				
			}

		}

	}
	

}

void UWG_Inventory_ItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UWG_Inventory_ItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent , InOperation);

	return true;
}

FReply UWG_Inventory_ItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{

		if (_inventory.IsValid())
		{
	
			if (_item == nullptr)
				return reply.NativeReply;
			
			EItemTypes itemType = _item->GetItemType();
		
			if (itemType == EItemTypes::WEAPON || itemType == EItemTypes::ARMOR)
			{
				EquipItem();
			}

			else if (itemType == EItemTypes::CONSUMABLE)
			{

			}

		}

	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Left Click"));
	}
	


	return reply.NativeReply;
}
