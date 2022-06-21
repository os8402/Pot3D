// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_Inventory.h"

#include "Item/OBJ_Item.h"

#include "UI/WG_Drag.h"

#include <Components/WrapBox.h>
#include <Blueprint/WidgetTree.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

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

	UWG_Drag* dragDropOperation = NewObject<UWG_Drag>();


	dragDropOperation->_widgetRef = this;
	dragDropOperation->_dragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	dragDropOperation->DefaultDragVisual = this;
	dragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = dragDropOperation;

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging again"));
}

bool UWG_Inventory_ItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent , InOperation);

	return true;
}

FReply UWG_Inventory_ItemSlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);



	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Right Click"));

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
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Left Click"));

		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton );
	}
	
	return reply.NativeReply;
}
