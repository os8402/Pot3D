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
}


void UWG_Inventory_ItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UWG_Drag* dragDropOperation = NewObject<UWG_Drag>();

	dragDropOperation->_widgetRef = this;
	dragDropOperation->_dragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	dragDropOperation->DefaultDragVisual = this;
	dragDropOperation->Pivot = EDragPivot::MouseDown;

	dragDropOperation->SetSlot(this);

	OutOperation = dragDropOperation;

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Dragging"));
}

bool UWG_Inventory_ItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent , InOperation);


	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Item Drop"));

	UWG_Drag* dragDropOperation = Cast<UWG_Drag>(InOperation);

	if (dragDropOperation)
	{
		int32 prevSlotNum = dragDropOperation->GetSlot()->GetSlotNum();
		int32 currentSlotNum = GetSlotNum();


		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Item Slot %d , Current Num %d") , 
			prevSlotNum, currentSlotNum));

		if(prevSlotNum == currentSlotNum)
			return false;

		_inventory->ChangeItemSlot(prevSlotNum , currentSlotNum);


		return true;
	}
	
	return false; 


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

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Left Click %d") , GetSlotNum()));

		if(GetItem() == nullptr)
			return reply.NativeReply;

		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton );
	}
	
	return reply.NativeReply;
}
