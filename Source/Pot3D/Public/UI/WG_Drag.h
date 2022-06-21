// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WG_Drag.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_Drag : public UDragDropOperation
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* _widgetRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D _dragOffset;



	
	
};
