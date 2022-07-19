// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "WG_Slot.generated.h"

class UWG_Inventory;
class UOBJ_Item;
class UTexture2D;
class UButton;

UCLASS()
class POT3D_API UWG_Slot : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;
	virtual void RefreshUI();
	

	UButton* GetSlotBtn() { return _BTN_Slot; }

	void SetSlotNum(int32 num) { _slotNum = num; }
	int32 GetSlotNum() { return _slotNum; }
	
	ESlotTypes GetSlotType() {return _slotType;}



protected:

	UPROPERTY(EditAnywhere , Category = "Slot" , meta = (AllowPrivateAccess = true))
	ESlotTypes _slotType;

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;

	UPROPERTY(meta = (BindWidget))
	UButton* _BTN_Slot;

	int32 _slotNum;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* _texture;





};
