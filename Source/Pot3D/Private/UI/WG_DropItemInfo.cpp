// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_DropItemInfo.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Item/OBJ_Item.h"

void UWG_DropItemInfo::BindItemInfo(class UOBJ_Item* item)
{
	FText name = item->GetItemName();
	int32 count = item->GetCount();
	bool isConsumable = item->GetIsConsumable();
	ERarity rarity = item->GetRarity();

	FString conv;

	if (isConsumable)
	{
		conv = FString::Printf(TEXT("%s %d"), *name.ToString(), count);
	}
	else
	{
		conv = FString::Printf(TEXT("%s"), *name.ToString());
	}

	FLinearColor color;

	switch (rarity)
	{
	case ERarity::NORMAL:
		color = FLinearColor::White;
		break;
	case ERarity::RARE:
		color = FLinearColor(0.2f ,0.4f , 1, 1);
		break;
	case ERarity::UNIQUE:
		color = FLinearColor(1, 0.3f, 1, 1);
		break;
	case ERarity::LEGENDARY:
		color = color = FLinearColor(1, 0.5f, 0.1f, 1);
		break;	
	default:
		break;
	}

	_TB_ItemName->SetColorAndOpacity(color);


	_TB_ItemName->SetText(FText::FromString(conv));

}

void  UWG_DropItemInfo::LookItem()
{
	//_IMG_BG->SetColorAndOpacity();
}	
