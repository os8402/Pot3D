// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WG_Drag.generated.h"

/**
 * 
 */
class UWG_Slot;

UCLASS()
class POT3D_API UWG_Drag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UWG_Slot* GetSlot(){ return _slot;}
	void SetSlot(UWG_Slot* slot) {_slot = slot;}

private:

	UPROPERTY()
	UWG_Slot* _slot;
	
};
