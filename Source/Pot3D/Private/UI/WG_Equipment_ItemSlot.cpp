// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Equipment_ItemSlot.h"
#include "Item/OBJ_Item.h"
#include "Components/Image.h"

void UWG_Equipment_ItemSlot::NativePreConstruct()
{
	RefreshUI();
}

void UWG_Equipment_ItemSlot::RefreshUI()
{
	//빈 장비
	if (_item == nullptr)
	{	
		_color = FLinearColor(.2f, .2f, .2f, .6f);
		//TODO : 파츠별 컬러 및 아이콘
		_IMG_Icon->SetColorAndOpacity(_color);
		_IMG_Icon->SetBrushFromTexture(_TEX_EmptyIcon);
		return;
	}


	_color = FLinearColor::White;
	_IMG_Icon->SetBrushFromTexture(_texture);
	

}	

void UWG_Equipment_ItemSlot::SetItem(UOBJ_Item* item)
{
	if (item == nullptr)
		return;

	_item = item;

	//TODO : Texture Set

	UTexture2D* newTexture = Cast<UTexture2D>(
		StaticLoadObject(UTexture2D::StaticClass(), nullptr, *item->GetTexturePath().ToString()));

	if (newTexture != nullptr)
		_texture = newTexture;

	RefreshUI();
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

	return reply.NativeReply;
}
