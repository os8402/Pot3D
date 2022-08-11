// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_MainBar.generated.h"

class UWG_MainBar_Slot;
class UWG_IngameMain;
class UWG_Buff;

UCLASS()
class POT3D_API UWG_MainBar : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void BindStat(class UACP_StatInfo* statComp);

	void UpdateHp();
	void UpdateMp();


	void AddBuffList(int32 value , EBuffTypes buffType);

	void ChangeTooltip(FText text);

	void SetSlotTooltipHovered(UWG_MainBar_Slot* slot);

	void SetUIOwner(UWG_IngameMain* owner) {_UIOwner = owner;}

	UWG_MainBar_Slot* GetMainBarSlot(int32 id){ return _mainBarSlots[id]; }

	UWG_MainBar_Slot* CheckExistSlot(int32 skillId);

	void TestPreSlot();

private:
	
	TWeakObjectPtr<UWG_IngameMain> _UIOwner;

	UPROPERTY()
	TSubclassOf<UWG_MainBar_Slot> _mainBarSlotClass;
	UPROPERTY()
	TSubclassOf<UWG_Buff> _buffClass;

	TWeakObjectPtr<class UACP_StatInfo> _currentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UWG_GlassBallBar* _GB_HpBar;
	UPROPERTY(meta = (BindWidget))
	class UWG_GlassBallBar* _GB_MpBar;

	UPROPERTY(meta = (BindWidget))
	class UButton* _BTN_Inventory;
	UPROPERTY(meta = (BindWidget))
	class UButton* _BTN_Skill;
	UPROPERTY(meta = (BindWidget))
	class UButton* _BTN_Quest;
	UPROPERTY(meta = (BindWidget))
	class UButton* _BTN_Menu;


	UPROPERTY(meta = (BindWidget))
	class UWG_Tooltip_Gauge* _WBP_Tooltip_Hp;
	UPROPERTY(meta = (BindWidget))
	class UWG_Tooltip_Gauge* _WBP_Tooltip_Mp;
	UPROPERTY(meta = (BindWidget))
	class UWG_Tooltip_MainBar* _WBP_Tooltip_MainBar;
	UPROPERTY(meta = (BindWidget))
	class UWG_Tooltip* _WBP_Tooltip;


	TArray<UWG_MainBar_Slot*> _mainBarSlots;


};

