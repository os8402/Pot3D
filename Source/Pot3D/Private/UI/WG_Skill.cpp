#include "UI/WG_Skill.h"
#include "UI/WG_Skill_List.h"
#include "UI/WG_Button.h"

#include "Skill/ACP_SKillInfo.h"
#include "Creature/UNIT_Player.h"

#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/TextBlock.h>
#include <Blueprint/WidgetTree.h>
#include <Components/ScrollBox.h>

void UWG_Skill::NativePreConstruct()
{
	Super::NativePreConstruct();

	UClass* skillList =  StaticLoadClass(UWG_Skill_List::StaticClass(), nullptr,
		TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Skill/WBP_Skill_List.WBP_Skill_List_C'"));

	_skillListClass = skillList;


	UButton* activeBtn = _BTN_Active->GetSlotBtn();
	UButton* passiveBtn = _BTN_Passive->GetSlotBtn();

	activeBtn->OnClicked.AddDynamic(this, &UWG_Skill::ConvertActiveSwitcher);
	passiveBtn->OnClicked.AddDynamic(this, &UWG_Skill::ConvertPassiveSwitcher);

}


void UWG_Skill::InitializeUI()
{
	UACP_SKillInfo* skillInfo = _currentOwner->GetSkillComp();

	if(skillInfo == nullptr)
		return;


	UScrollBox* sbActive = WidgetTree->FindWidget<UScrollBox>("_SB_ActiveList");
	UScrollBox* sbPassive = WidgetTree->FindWidget<UScrollBox>("_SB_PassiveList");

	//ACTIVE
	
	TMap<int32, FSkillData*> activeSkills = skillInfo->GetActiveSkills();
	TMap<int32, FSkillData*> passiveSkills = skillInfo->GetPassiveSkills();
	SetSkillListData(sbActive, activeSkills);
	SetSkillListData(sbPassive, passiveSkills);

}


void UWG_Skill::SetSkillListData(UScrollBox* sbList, TMap<int32, FSkillData*> skills)
{

	UACP_SKillInfo* skillInfo = _currentOwner->GetSkillComp();

	TMap<int32, FSkillData*> acquiredSkills = skillInfo->GetAcquiredSkills();

	if (sbList && IsValid(_skillListClass))
	{
		sbList->ClearChildren();

		for (const auto& skill : skills)
		{

			UWG_Skill_List* skillList = CreateWidget<UWG_Skill_List>(this, _skillListClass);
			sbList->AddChild(skillList);

			skillList->SetUIOwner(this);

			FSkillData* skillData = skill.Value;

			bool bAcquired = acquiredSkills.Find(skill.Key) ? true : false; 

			skillList->SetSkillData(skillData , bAcquired);

		}

	}
}

void UWG_Skill::RefreshUI()
{

}



void UWG_Skill::AcquireSkill(int32 id, FSkillData* skillData)
{

	_currentOwner->GetSkillComp()->SetAcquireSkill(id , skillData);
}

void UWG_Skill::ConvertActiveSwitcher()
{
	_WS_Switcher->SetActiveWidgetIndex(0);

}
	

void UWG_Skill::ConvertPassiveSwitcher()
{
	_WS_Switcher->SetActiveWidgetIndex(1);

}
