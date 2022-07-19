﻿#include "UI/WG_MainBar.h"
#include "Stat/ACP_StatInfo.h"

#include "UI/WG_MainBar_Slot.h"
#include "UI/WG_GlassBallBar.h"
#include "UI/WG_Tooltip_Gauge.h"

#include <Blueprint/WidgetTree.h>
#include <Components/HorizontalBox.h>


void UWG_MainBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	//TODO : 나중에 문서로.. 
	UClass* mainbarSlotClass = StaticLoadClass(UWG_MainBar_Slot::StaticClass(), nullptr,
		TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Slot/WBP_MainBar_Slot.WBP_MainBar_Slot_C'"));

	_mainBarSlotClass = mainbarSlotClass;

	_GB_HpBar->SetToolTip(_WBP_Tooltip_Hp);
	_WBP_Tooltip_Hp->SetUIName(FText::FromString(TEXT("생명력")));
	_WBP_Tooltip_Hp->SetUIInfo(FText::FromString(TEXT("생명력이 모두 떨어지면 죽습니다.")));
	_WBP_Tooltip_Hp->SetStatType(EStatTypes::HP);

	_GB_MpBar->SetToolTip(_WBP_Tooltip_Mp);
	_WBP_Tooltip_Mp->SetUIName(FText::FromString(TEXT("마력")));
	_WBP_Tooltip_Mp->SetUIInfo(FText::FromString(TEXT("마력이 모이면 스킬을 쓸 수 있습니다.")));
	_WBP_Tooltip_Mp->SetStatType(EStatTypes::MP);


	//Mainbar Slot 생성
	UHorizontalBox* hb_slotList = WidgetTree->FindWidget<UHorizontalBox>("_HB_SlotList");

	if (hb_slotList && IsValid(_mainBarSlotClass))
	{
		hb_slotList->ClearChildren();

		for (int i = 0; i < 7; i++)
		{

			UWG_MainBar_Slot* mainbarSlot = CreateWidget<UWG_MainBar_Slot>(this, _mainBarSlotClass);
			hb_slotList->AddChild(mainbarSlot);

			mainbarSlot->SetSlotNum(i + 1);
			mainbarSlot->RefreshUI();

		}

	}
	

}

void UWG_MainBar::BindStat(class UACP_StatInfo* statComp)
{
	_currentStatComp = statComp;
	_currentStatComp->GetOnHpChanged().AddUObject(this, &UWG_MainBar::UpdateHp);

	_WBP_Tooltip_Hp->SetStatComp(_currentStatComp.Get());
	_WBP_Tooltip_Mp->SetStatComp(_currentStatComp.Get());

	UpdateHp();
}

void UWG_MainBar::UpdateHp()
{
	if (_currentStatComp.IsValid())
	{
		_GB_HpBar->UpdateGauge(_currentStatComp->GetHpRatio());
	}

}
