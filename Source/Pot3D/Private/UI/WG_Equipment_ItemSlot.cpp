// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Equipment_ItemSlot.h"
#include "Item/OBJ_Item.h"
#include "Components/Image.h"

void UWG_Equipment_ItemSlot::NativePreConstruct()
{
	SetItemInfo(nullptr);
}

void UWG_Equipment_ItemSlot::SetItemInfo(UOBJ_Item* item)
{
	//빈 장비
	if (item == nullptr)
	{	
		_color = FLinearColor(.2f, .2f, .2f, .6f);
		//TODO : 파츠별 컬러 및 아이콘
		_IMG_Icon->SetColorAndOpacity(_color);
		_IMG_Icon->SetBrushFromTexture(_TEX_EmptyIcon);
		return;
	}


	_color = FLinearColor::White;

	

}	
