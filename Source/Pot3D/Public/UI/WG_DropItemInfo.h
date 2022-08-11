// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "WG_DropItemInfo.generated.h"


UCLASS()
class POT3D_API UWG_DropItemInfo : public UUserWidget
{
	GENERATED_BODY()


public:

	void BindItemInfo(class UOBJ_Item* item);

	void LookItem(FLinearColor color);

private:
	
	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Bg;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_ItemName;

};
