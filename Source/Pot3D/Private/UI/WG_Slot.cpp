// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Slot.h"
#include "Item/OBJ_Item.h"
#include "UI/WG_Inventory.h"

void UWG_Slot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_BTN_Slot->IsHovered() && _inventory.IsValid())
	{

		_inventory->SetItemTooltipHovered(_item);

	}

}

void UWG_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();

	RefreshUI();
}

void UWG_Slot::RefreshUI()
{

}

void UWG_Slot::SetItem(UOBJ_Item* item)
{

	_item = item;
	UTexture2D* newTexture = nullptr;

	if (item != nullptr)
	{	
		//TODO : Texture Set

		newTexture = Cast<UTexture2D>(
			StaticLoadObject(UTexture2D::StaticClass(), nullptr, *item->GetTexturePath().ToString()));
	
	}

	_texture = newTexture;

	RefreshUI();
}
