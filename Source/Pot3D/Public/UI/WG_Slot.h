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
class UImage;
struct FSkillData;

UCLASS()
class POT3D_API UWG_Slot : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;
	virtual void RefreshUI();
	virtual void SetTextureIcon(UTexture2D* texture);
	UTexture2D* GetTextureIcon() {return _iconTexture;}

	UButton* GetSlotBtn() { return _BTN_Slot; }

	void SetImage(UImage* img) {_IMG_Icon = img;}
	UImage* GetImage() {return _IMG_Icon;}

	void SetSlotNum(int32 num) { _slotNum = num; }
	int32 GetSlotNum() { return _slotNum; }
	
	void SetSlotType(ESlotTypes slotType) {_slotType = slotType;}
	ESlotTypes GetSlotType() {return _slotType;}

	void SetSkillData(FSkillData* skillData) { _skillData = skillData; }
	FSkillData* GetSkillData() { return _skillData; }

protected:

	UPROPERTY(EditAnywhere , Category = "Slot" , meta = (AllowPrivateAccess = true))
	ESlotTypes _slotType;

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;

	UPROPERTY(meta = (BindWidget))
	UButton* _BTN_Slot;

	int32 _slotNum;

	//쓰고 있다면 가져옴
	FSkillData* _skillData;


private:
	UTexture2D* _iconTexture;
};
