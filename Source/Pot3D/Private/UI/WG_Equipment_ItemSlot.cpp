// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Equipment_ItemSlot.h"
#include "UI/WG_Inventory.h"
#include "Item/OBJ_Item.h"
#include "Components/Image.h"

void UWG_Equipment_ItemSlot::RefreshUI()
{
	//�� ���
	if (_item == nullptr)
	{	
		_color = FLinearColor(.2f, .2f, .2f, .6f);
		_texture = _TEX_EmptyIcon;
	
	}
	else
	{
		_color = FLinearColor(1, 1, 1, 1);
	}



	_IMG_Icon->SetColorAndOpacity(_color);
	_IMG_Icon->SetBrushFromTexture(_texture);
	
	FString str = this->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);
}	


void UWG_Equipment_ItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UWG_Equipment_ItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return true;
}

FReply UWG_Equipment_ItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Equipment Left Click"));
	}

	return reply.NativeReply;
}
