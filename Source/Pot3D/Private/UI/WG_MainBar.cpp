#include "UI/WG_MainBar.h"
#include "Stat/ACP_StatInfo.h"

#include "UI/WG_MainBar_Slot.h"
#include "UI/WG_GlassBallBar.h"
#include "UI/WG_Tooltip_Gauge.h"
#include "UI/WG_Tooltip.h"

#include "UI/WG_IngameMain.h"
#include "UI/WG_Skill.h"
#include "UI/WG_Skill_List.h"
#include "UI/WG_Skill_Slot.h"

#include "UI/WG_Tooltip_MainBar.h"
#include "UI/WG_Buff.h"

#include "Manager/GI_GmInst.h"

#include "Manager/PS_PlayerState.h"

#include <Blueprint/WidgetTree.h>
#include <Components/HorizontalBox.h>


void UWG_MainBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	//TODO : 나중에 문서로.. 

	UtilsLib::GetTSubClass(&_mainBarSlotClass , TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Slot/WBP_MainBar_Slot.WBP_MainBar_Slot_C'"));
	UtilsLib::GetTSubClass(&_buffClass, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Buff/WBP_Buff.WBP_Buff_C'"));

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

	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto ps = Cast<APS_PlayerState>(pc->PlayerState);
	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));
	TMap<int32, int32> saveUsedSlots = ps->GetMainbarSlots();


	if (hb_slotList && IsValid(_mainBarSlotClass))
	{
		hb_slotList->ClearChildren();

		for (int i = 0; i < 7; i++)
		{

			UWG_MainBar_Slot* mainbarSlot = CreateWidget<UWG_MainBar_Slot>(this, _mainBarSlotClass);
			hb_slotList->AddChild(mainbarSlot);

			mainbarSlot->SetSlotNum(i + 1);
			mainbarSlot->RefreshUI();
			mainbarSlot->SetUIOwner(this);

			mainbarSlot->SetToolTip(_WBP_Tooltip_MainBar);
			//TODO : Get Save Data
			if (saveUsedSlots.Find(i + 1))
			{
				if (gmInst)
				{
					FSkillData* skillData = gmInst->GetTableData<FSkillData>(ETableDatas::SKILL, saveUsedSlots[i + 1]);
					//복사함
					mainbarSlot->CopySlotData(skillData);
				}
			}
	
			_mainBarSlots.Add(mainbarSlot);
		}

	}

	_BTN_Inventory->SetToolTip(_WBP_Tooltip);
	_BTN_Skill->SetToolTip(_WBP_Tooltip);
	_BTN_Quest->SetToolTip(_WBP_Tooltip);
	_BTN_Menu->SetToolTip(_WBP_Tooltip);
}

void UWG_MainBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(_BTN_Inventory->IsHovered())
		ChangeTooltip(FText::FromString(TEXT("인벤토리")));

	if (_BTN_Skill->IsHovered())
		ChangeTooltip(FText::FromString(TEXT("스킬")));

	if (_BTN_Quest->IsHovered())
		ChangeTooltip(FText::FromString(TEXT("퀘스트")));

	if (_BTN_Menu->IsHovered())
		ChangeTooltip(FText::FromString(TEXT("메뉴")));
}

void UWG_MainBar::BindStat(class UACP_StatInfo* statComp)
{
	_currentStatComp = statComp;
	_currentStatComp->GetOnHpChanged().AddUObject(this, &UWG_MainBar::UpdateHp);
	_currentStatComp->GetOnMpChanged().AddUObject(this, &UWG_MainBar::UpdateMp);

	_WBP_Tooltip_Hp->SetStatComp(_currentStatComp.Get());
	_WBP_Tooltip_Mp->SetStatComp(_currentStatComp.Get());

	UpdateHp();
	UpdateMp();
}

void UWG_MainBar::UpdateHp()
{
	if (_currentStatComp.IsValid())
	{
		_GB_HpBar->UpdateGauge(_currentStatComp->GetHpRatio());
	}

}

void UWG_MainBar::UpdateMp()
{
	if (_currentStatComp.IsValid())
	{
		_GB_MpBar->UpdateGauge(_currentStatComp->GetMpRatio());
	}
}


void UWG_MainBar::AddBuffList(int32 value , EBuffTypes buffType)
{
	//Mainbar Slot 생성
	UHorizontalBox* hb_buffBox = WidgetTree->FindWidget<UHorizontalBox>("_HB_BuffBox");

	UWG_Buff* buffSlot = CreateWidget<UWG_Buff>(this, _buffClass);
	hb_buffBox->AddChild(buffSlot);


	buffSlot->RefreshUI(value,  buffType);
	buffSlot->SetUIOwner(this);

	buffSlot->SetToolTip(_WBP_Tooltip);

}

void UWG_MainBar::ChangeTooltip(FText text)
{
	_WBP_Tooltip->SetNameText(text);
}

void UWG_MainBar::SetSlotTooltipHovered(UWG_MainBar_Slot* slot)
{
	FSkillData* skillData = slot->GetSkillData();

	if (skillData == nullptr)
	{
		_WBP_Tooltip_MainBar->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	

	_WBP_Tooltip_MainBar->SetTooltipFromData(skillData);
	_WBP_Tooltip_MainBar->SetVisibility(ESlateVisibility::Visible);

}



UWG_MainBar_Slot* UWG_MainBar::CheckExistSlot(int32 skillId)
{
	for (const auto& slot : _mainBarSlots)
	{
		ESlotTypes slotType = slot->GetSlotType();
		FSkillData* skillData = slot->GetSkillData();

		if(slotType == ESlotTypes::NONE || skillData == nullptr)
			continue;
		
		int32 checkSKillId = skillData->_skillId;

		if (checkSKillId == skillId)
		{
			return slot;
		}
	}

	return nullptr;
}

void UWG_MainBar::TestPreSlot()
{
	//TEST CODE
	TArray<UWG_Skill_List*> activeSkillList = _UIOwner->GetSkillPanel()->GetActiveSkillList();


	for (int i = 0; i < 3; i++)
	{
		UWG_Skill_Slot* skillSlot = activeSkillList[i]->GetSkillSlot();
		FSkillData* skillData = skillSlot->GetSkillData();

		_mainBarSlots[i]->SetSlotType(ESlotTypes::SKILL);
		UTexture2D* newTexture = skillSlot->GetTextureIcon();
		_mainBarSlots[i]->SetTextureIcon(newTexture);
		_mainBarSlots[i]->SetConditionToUseSlot(skillData);

	}

	/// <summary>
	/// 나중에 지워야 함 
	/// </summary>
}
