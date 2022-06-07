// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_Inventory.h"
#include "Item/OBJ_Item.h"

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

	if (_BTN_Slot->IsHovered() && _inventory)
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
