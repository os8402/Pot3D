// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Equipment_ItemSlot.h"
#include "UI/WG_Inventory.h"
#include "Item/OBJ_Item.h"

#include "UI/WG_Drag.h"
#include "Components/Image.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UWG_Equipment_ItemSlot::RefreshUI()
{
	//ºó Àåºñ
	if (_item == nullptr)
	{	
		_color = FLinearColor(.2f, .2f, .2f, .6f);
		SetTextureIcon(_TEX_EmptyIcon);
	
	}
	else
	{
		_color = FLinearColor(1, 1, 1, 1);
	}

	_IMG_Icon->SetColorAndOpacity(_color);

}	


void UWG_Equipment_ItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
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

bool UWG_Equipment_ItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return true;
}

FReply UWG_Equipment_ItemSlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{

		if (_inventory.IsValid())
		{

			if (_item == nullptr)
				return reply.NativeReply;

			_inventory->UnEquipItem(_item);

		}

	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Equipment Left Click"));
		
		if (GetItem() == nullptr)
			return reply.NativeReply;

		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	
	}

	return reply.NativeReply;
}
