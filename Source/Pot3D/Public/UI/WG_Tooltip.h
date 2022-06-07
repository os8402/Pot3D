// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "WG_Tooltip.generated.h"


class UOBJ_Item;

UCLASS()
class POT3D_API UWG_Tooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshUI(UOBJ_Item* item);
	void Localization(UOBJ_Item* item);

private:
	

	UPROPERTY(meta = (BindWidget))
	class UWG_TitleBar* _WBP_TitleBar;

	UPROPERTY(meta = (BindWidget))
	class UWG_Inventory_ItemSlot* _WBP_Inventory_ItemSlot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Grade;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Amount;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_AmountInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_ItemType;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_SellGold;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Durability;



	EItemWeaponTypes _itemWeaponType;
	EItemArmorTypes _itemArmorType;
	EItemConsumableTypes _itemConsumableType;

};
