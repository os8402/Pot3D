// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Inventory_ItemSlot.generated.h"

/**
 * 
 */

class UWG_Inventory;
class UOBJ_Item;
class UTexture2D;
class UButton;

UCLASS()
class POT3D_API UWG_Inventory_ItemSlot : public UUserWidget
{
	GENERATED_BODY()




public:

	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void RefreshUI();


	void SetInventory(UWG_Inventory* inventory) {_inventory = inventory; }

	UButton* GetSlotBtn() {return _BTN_Slot;}
	

	void SetItem(UOBJ_Item* item);
	UOBJ_Item* GetItem() { return _item; }


	void SetSlotNum(int32 num) {_slotNum = num;}
	int32 GetSlotNum() {return _slotNum;}




private:
	
	UPROPERTY()
	UWG_Inventory* _inventory;
	
	UPROPERTY(meta = (BindWidget))
	UButton* _BTN_Slot;

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;

	UPROPERTY(EditAnywhere, Category="SLOT")
	int32 _slotNum;

	UPROPERTY()
	UOBJ_Item* _item;

	UPROPERTY(VisibleAnywhere )
	UTexture2D* _texture;
};
