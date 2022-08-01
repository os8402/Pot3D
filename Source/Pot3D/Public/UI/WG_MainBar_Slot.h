#pragma once

#include "CoreMinimal.h"
#include "UI/WG_Slot.h"
#include "UtilsLib.h"
#include "Data/GameDataTable.h"
#include "WG_MainBar_Slot.generated.h"


class UWG_MainBar;

UCLASS()
class POT3D_API UWG_MainBar_Slot : public UWG_Slot
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void RefreshUI() override;

	void SetUISlotFromData(UWG_Slot* slot);

	void SetUIOwner(UWG_MainBar* mainBar) { if (mainBar) 	_UIOwner = mainBar; }
	
	void TickSlotCoolTime(float InDeltaTime);

	void SetMaxCoolTime(float maxCoolTime) {_maxCoolTime = maxCoolTime;}

	float GetCoolTimeRatio() {return _coolTime/ _maxCoolTime;}
	bool GetCoolTimeFlag() {return _bCoolTimeFlag;}

	//슬롯 이벤트 활성을 위한 조건.. 
	//아마 게임이 좀 커지?면 매개 변수에 객체 함수로 바꿀 수도
	void SetConditionToUseSlot(FSkillData* skillData)
	{
		_skillData = skillData;

		if (skillData != nullptr)
			SetMaxCoolTime(skillData->_coolTime);
	}

	bool CanUseSkillEvent(int32 condition);

	void StartSkillEvent();

	int32 GetSKillId( ){ return (_skillData) ? _skillData->_skillId : -1; }


private:

	TWeakObjectPtr<UWG_MainBar> _UIOwner;

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_CoolTime;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_SlotIndex;
	
	UPROPERTY(VisibleAnywhere, Category="CoolTime")
	UMaterialInstanceDynamic* _MID_coolTime;

	UPROPERTY()
	float _coolTime = 0;
	UPROPERTY(VisibleAnywhere, Category = "Condition")
	float _maxCoolTime = 1;
	UPROPERTY(VisibleAnywhere, Category = "Condition")
	bool _bCoolTimeFlag = false;

	//슬롯이 비었을 경우 보이게 될 텍스처
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTexture2D* _TEX_EmptyIcon;



};
