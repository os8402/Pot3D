// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WG_Drag.generated.h"

/**
 * 
 */
class UWG_ItemSlot;

UCLASS()
class POT3D_API UWG_Drag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UWG_ItemSlot* GetSlot(){ return _slot;}
	void SetSlot(UWG_ItemSlot* slot) {_slot = slot;}

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* _widgetRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D _dragOffset;

private:

	UPROPERTY()
	UWG_ItemSlot* _slot;
	
};