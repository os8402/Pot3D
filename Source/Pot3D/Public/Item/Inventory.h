// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inventory.generated.h"

// This class does not need to be modified.

class UOBJ_Item;
class UWG_Inventory_ItemSlot;

UINTERFACE(MinimalAPI)
class UInventory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POT3D_API IInventory
{
	GENERATED_BODY()

public:
	virtual TMap<int32, UWG_Inventory_ItemSlot*>& GetInventoryData() = 0;


	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual bool AddItem(UOBJ_Item* newItem) = 0;
	virtual void RemoveItem(int32 slot) = 0;
	virtual void UseItem(int32 slot) = 0;
	virtual void RefreshInventory() = 0;
	virtual int32 GetEmptySlot() = 0;
};
