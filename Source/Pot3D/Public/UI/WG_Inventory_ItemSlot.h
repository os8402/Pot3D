// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Inventory_ItemSlot.generated.h"

/**
 * 
 */

class UOBJ_Item;
class UTexture2D;

UCLASS()
class POT3D_API UWG_Inventory_ItemSlot : public UUserWidget
{
	GENERATED_BODY()




public:

	virtual void NativePreConstruct() override;
	void RefreshUI();


	void SetItem(UOBJ_Item* item);
	UOBJ_Item* GetItem() { return _item; }


	void SetSlotNum(int32 num) {_slotNum = num;}
	int32 GetSlotNum() {return _slotNum;}




private:
	
	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;

	UPROPERTY(EditAnywhere, Category="SLOT")
	int32 _slotNum;

	UPROPERTY()
	UOBJ_Item* _item;

	UPROPERTY(VisibleAnywhere )
	UTexture2D* _texture;
};
