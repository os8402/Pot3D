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

UCLASS()
class POT3D_API UWG_Inventory : public UUserWidget, public IInventory
{
	GENERATED_BODY()

public:
	class UWG_Status* GetStatus() {return _WBP_Status;}

public:
	virtual TMap<int32, UOBJ_Item*>& GetInventoryData() { return _inventoryData; }

public:
	//ITEM

	virtual bool AddItem(UOBJ_Item* newItem);
	virtual void RemoveItem(int32 slot);
	virtual void UseItem(int32 slot);
	virtual void RefreshInventory();
	virtual int32 GetEmptySlot();

private:
	TMap<int32, UOBJ_Item*> _inventoryData;
	int32 _itemMaxSlot = 20;


private:

	UPROPERTY(meta = (BindWidget))
	class UWG_Status* _WBP_Status;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Gold;


};
