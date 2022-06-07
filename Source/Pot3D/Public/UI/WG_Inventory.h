// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Inventory.h"
#include "UEnumHeader.h"
#include "Blueprint/UserWidget.h"
#include "WG_Inventory.generated.h"

/**
 * 
 */

 class UOBJ_Item;
 class UWG_Inventory_ItemSlot;



UCLASS()
class POT3D_API UWG_Inventory : public UUserWidget, public IInventory
{
	GENERATED_BODY()

public:
	
	virtual void NativePreConstruct() override;
	class UWG_Status* GetStatus() {return _WBP_Status;}


public:
	virtual TMap<int32, UWG_Inventory_ItemSlot*>& GetInventoryData() { return _inventoryData; }

public:
	//ITEM

	virtual bool AddItem(UOBJ_Item* newItem);
	virtual void RemoveItem(int32 slot);
	virtual void UseItem(int32 slot);
	virtual void RefreshInventory();
	virtual int32 GetEmptySlot();

	void SetItemTooltipHovered(UOBJ_Item* item);

private:

	UPROPERTY(EditAnywhere, Category="Item Slot")
	TSubclassOf<UWG_Inventory_ItemSlot> _itemSlotClass; 


	//TMap<int32, UOBJ_Item*> _inventoryData;
	TMap<int32, UWG_Inventory_ItemSlot*> _inventoryData;
	int32 _itemMaxSlotNum = 20;


private:

	UPROPERTY(meta = (BindWidget))
	class UWG_Status* _WBP_Status;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Gold;
	
	UPROPERTY(meta = (BindWidget))
	class UWG_Tooltip* _WBP_Tooltip;

	TWeakObjectPtr<UOBJ_Item> _hoveredItem;

};
