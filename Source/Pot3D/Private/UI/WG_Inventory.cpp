// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Inventory.h"
#include "Item/OBJ_Item.h"
#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_Tooltip.h"
#include "Manager/GI_GmInst.h"

#include <Components/WidgetComponent.h>
#include <Components/WrapBox.h>
#include <COmponents/Button.h>
#include <Blueprint/WidgetTree.h>

#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>


void UWG_Inventory::NativePreConstruct()
{
	Super::NativePreConstruct();

	UWrapBox* slotBox = WidgetTree->FindWidget<UWrapBox>("_WBOX_SlotBox");

	if (slotBox && IsValid(_itemSlotClass))
	{
		for (int i = 0; i < _itemMaxSlotNum; i++)
		{
			UWG_Inventory_ItemSlot* itemSlot = CreateWidget<UWG_Inventory_ItemSlot>(this, _itemSlotClass);
			slotBox->AddChild(itemSlot);

			itemSlot->SetInventory(this);
			itemSlot->SetSlotNum(i);

			_inventoryData.Add(i, itemSlot);
		
			itemSlot->SetToolTip(_WBP_Tooltip);
			itemSlot->ToolTipWidget->SetRenderTranslation(FVector2D(-500,0));


		}
	

	}
}



bool UWG_Inventory::AddItem(UOBJ_Item* newItem)
{
	if (newItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add Item Failed"));
		return false;
	}


	int32 emptySlot = GetEmptySlot();


	if (emptySlot == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Is Full"));
		return false;

	}

	EItemTypes itemtype = newItem->GetItemType();

	if (itemtype == EItemTypes::GOLD || itemtype == EItemTypes::JEWEL)
	{
		// TODO : 재화 처리
		if (itemtype == EItemTypes::GOLD)
		{
			auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (gmInst)
			{
				gmInst->SetGold(newItem->GetCount());
			}
		}
	}

	else
	{
		_inventoryData[emptySlot]->SetItem(newItem);

		FString str = FString::Printf(TEXT("Get Item :  %s"), *newItem->GetItemName().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);
	}



	RefreshInventory();

	return true;

}

void UWG_Inventory::RemoveItem(int32 slot)
{
	_inventoryData.Remove(slot);
	RefreshInventory();
}

void UWG_Inventory::UseItem(int32 slot)
{
	//_inventoryData[slot]->_count -= 1;
	RefreshInventory();
}

void UWG_Inventory::RefreshInventory()
{
	//Gold 
	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gmInst)
	{
		int32 gold = gmInst->GetGold();
		_TB_Gold->SetText(FText::FromString(FString::FromInt(gold)));

		FString goldStr = FString::Printf(TEXT("Add Gold :  %d"), gold);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green , goldStr);
	}


	//Item Info Setting
	
	for (int i = 0; i < _itemMaxSlotNum; i++)
	{
		_inventoryData[i]->RefreshUI();
	}

}

int32 UWG_Inventory::GetEmptySlot()
{
	int32 emptySlot = -1;

	//빈 슬롯 ㅊㅔ크
	for (int32 i = 0; i < _itemMaxSlotNum; i++)
	{
		UOBJ_Item* isItem = _inventoryData[i]->GetItem();

		if (isItem == nullptr)
		{
			return i;
		}
	}

	return emptySlot;
}

void UWG_Inventory::SetItemTooltipHovered(UOBJ_Item* item)
{

	if (item == nullptr)
	{
		_WBP_Tooltip->SetVisibility(ESlateVisibility::Hidden);

		if (_hoveredItem.IsValid())
			_hoveredItem.Reset();

		return;
	}

	if(_hoveredItem == item)
		return;

	_hoveredItem = item;

	_WBP_Tooltip->SetVisibility(ESlateVisibility::Visible);

	FString goldStr = FString::Printf(TEXT("Item Info :  %s"), *item->GetItemName().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, goldStr);

	//TODO : 툴팁 정보 갱신

	_WBP_Tooltip->RefreshUI(item);
}
