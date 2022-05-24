// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Inventory_ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_Inventory_ItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FLinearColor _color;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UTexture2D* _TEX_Icon;
	

private:
	
	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;
};
