// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "WG_Slot.generated.h"

class UWG_Inventory;
class UOBJ_Item;
class UTexture2D;
class UButton;

UCLASS()
class POT3D_API UWG_Slot : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;
	virtual void RefreshUI();


	UButton* GetSlotBtn() { return _BTN_Slot; }

	void SetItem(UOBJ_Item* item);
	UOBJ_Item* GetItem() { return _item; }

	void SetInventory(UWG_Inventory* inventory) { _inventory = inventory; }


	void SetSlotNum(int32 num) { _slotNum = num; }
	int32 GetSlotNum() { return _slotNum; }

public:
	UPROPERTY(EditAnywhere)
	ESlotTypes _slotType;

protected:

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;

	UPROPERTY(meta = (BindWidget))
	UButton* _BTN_Slot;

	UPROPERTY(EditAnywhere, Category = "SLOT")
	int32 _slotNum;

	UPROPERTY()
	UOBJ_Item* _item;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* _texture;

	TWeakObjectPtr<UWG_Inventory> _inventory;



};
