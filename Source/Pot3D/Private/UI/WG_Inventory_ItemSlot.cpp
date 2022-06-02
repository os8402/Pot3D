// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory_ItemSlot.h"
#include "Components/Image.h"

void UWG_Inventory_ItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetItemInfo(_TEX_Icon);
}


void UWG_Inventory_ItemSlot::SetItemInfo(UTexture2D* texture)
{
	_IMG_Icon->SetColorAndOpacity(_color);

	_IMG_Icon->SetBrushFromTexture(texture);
}
