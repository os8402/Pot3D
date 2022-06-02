// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "WG_Equipment_ItemSlot.generated.h"


class UTexture2D;
class UOBJ_Item;

UCLASS()
class POT3D_API UWG_Equipment_ItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	void SetItemInfo(UOBJ_Item* item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FLinearColor _color;


	//장비 착용안 했을 경우 보이게 될 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTexture2D* _TEX_EmptyIcon;
	

public:

	EItemTypes _itemType = EItemTypes::NONE;	

private:

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;

};
