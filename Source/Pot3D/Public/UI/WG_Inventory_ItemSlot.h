// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "UI/WG_Slot.h"
#include "WG_Inventory_ItemSlot.generated.h"

/**
 * 
 */

class UWG_Inventory;
class UOBJ_Item;
class UTexture2D;
class UButton;

UCLASS()
class POT3D_API UWG_Inventory_ItemSlot : public UWG_Slot
{
	GENERATED_BODY()

public:


	virtual void RefreshUI() override;


protected:
	
	void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;


};
