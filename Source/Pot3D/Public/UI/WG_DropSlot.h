// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_DropSlot.generated.h"

/**
 * 
 */
 class UWG_ItemSlot;

UCLASS()
class POT3D_API UWG_DropSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnItem(UWG_ItemSlot* slot);

protected:
	void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


private:
	class AUNIT_Player* _player; 
	class UWG_Inventory* _inventory;



	UPROPERTY(EditAnywhere, Category="ItemSpawn")
	TSubclassOf<class AACT_DropItem> _ACT_DropItem;
};
