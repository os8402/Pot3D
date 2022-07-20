#pragma once

#include "CoreMinimal.h"
#include "UI/WG_Slot.h"
#include "UtilsLib.h"
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
	void SetUIOwner(UWG_MainBar* mainBar) { if (mainBar) 	_UIOwner = mainBar; }
	
	void TickSlotCoolTime(float InDeltaTime);

	void SetReduceMana(float reduceMana) {_reduceMana = reduceMana;}
	void SetMaxCoolTime(float maxCoolTime) {_maxCoolTime = maxCoolTime;}

	float GetCoolTimeRatio() {return _coolTime/ _maxCoolTime;}
	bool GetCoolTimeFlag() {return _bCoolTimeFlag;}


	//���� �̺�Ʈ Ȱ���� ���� ����.. 
	//�Ƹ� ������ �� Ŀ��?�� �Ű� ������ ��ü �Լ��� �ٲ� ����
	void SetConditionValue(int32 mana, float coolTime)
	{
		SetReduceMana(mana);
		SetMaxCoolTime(coolTime);
	}

	bool CanUseSkillEvent(int32 condition);

	void StartSkillEvent();



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
	UPROPERTY(VisibleAnywhere, Category = "Condition")
	float _reduceMana = 0.f;



	//������ ����� ��� ���̰� �� �ؽ�ó
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTexture2D* _TEX_EmptyIcon;



};
