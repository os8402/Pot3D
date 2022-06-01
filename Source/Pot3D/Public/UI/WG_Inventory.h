// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	class UWG_Status* GetStatus() {return _WBP_Status;}

	void RefreshInventory();

private:

	UPROPERTY(meta = (BindWidget))
	class UWG_Status* _WBP_Status;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Gold;
};
