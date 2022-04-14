// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_DropItemInfo.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_DropItemInfo : public UUserWidget
{
	GENERATED_BODY()


public:

	void BindItemInfo(FText name, int32 count);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_ItemName;

};
