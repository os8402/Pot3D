// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_Inventory.h"

#include "Item/OBJ_Item.h"

#include <Components/WrapBox.h>
#include <Blueprint/WidgetTree.h>
#include <Components/Image.h>
#include <COmponents/Button.h>


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
				_inventory->EquipItem(GetSlotNum()); 
			}

			else if (itemType == EItemTypes::CONSUMABLE)
			{
				_inventory->UseItem(GetSlotNum());
			}

		}

	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Left Click"));
	}
	


	return reply.NativeReply;
}
