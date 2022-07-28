#include "UI/WG_Skill_List.h"
#include "UI/WG_Skill.h"
#include "UI/WG_Skill_Slot.h"
#include <Components/TextBlock.h>
#include <Components/RichTextBlock.h>
#include <Components/Button.h>
#include <Components/Border.h>


void UWG_Skill_List::NativePreConstruct()
{
	Super::NativePreConstruct();


}

void UWG_Skill_List::SetSkillData(FSkillData* skillData, bool bAcquired)
{
	
	if(skillData != nullptr)
		_skillData = skillData;

	UTexture2D* newTexture = Cast<UTexture2D>(
		StaticLoadObject(UTexture2D::StaticClass(), nullptr, *skillData->_iconPath.ToString()));

	_WBP_Skill_Slot->SetTextureIcon(newTexture);
	_WBP_Skill_Slot->SetSlotLocked(!bAcquired);
	_WBP_Skill_Slot->SetSkillData(skillData);

	_TB_SkillName->SetText(skillData->_skillNameUI);

	_BD_Lock->SetRenderOpacity(1.f);


	if (bAcquired)
	{
		_BD_Lock->SetRenderOpacity(0.f);

		FString reduceStr = FString::Printf(TEXT("<White>소모 : 마나</> <Green>%d</>"), skillData->_reduceMana);
		_RTB_ReduceMana->SetText(FText::FromString(reduceStr));

		FString coolTimevalueStr = FString::SanitizeFloat(skillData->_coolTime);
		FString coolTimeStr = FString::Printf(TEXT("<White>재사용 대기 시간 :</> <Green>%s</><White>초</>"), *coolTimevalueStr);


		_RTB_CoolTime->SetText(FText::FromString(coolTimeStr));
		_RTB_SkillInfo->SetText(skillData->_skillInfo);

		//TODO : Remove btn delegate

	}
	else
	{
		FString requestStr = FString::Printf(TEXT("<White>플레이어 레벨</> <Green>%d</><White> 달성 시 습득 가능</>"), skillData->_requestLevel);
		_RTB_SkillInfo->SetText(FText::FromString(requestStr));
		//TODO : add  btn delegate

		_BTN_AddSkill->OnClicked.AddDynamic(this, &UWG_Skill_List::AcquireSkill);
		_BTN_RemoveSkill->SetIsEnabled(false);
	}

}

void UWG_Skill_List::AcquireSkill()
{

	_BTN_AddSkill->OnClicked.Clear();

	_BTN_AddSkill->SetIsEnabled(false);
	_BTN_RemoveSkill->SetIsEnabled(false);

	SetSkillData(_skillData, true);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill List Acquire Skill"));

	//TODO : 어떤 스킬을 배웠는지 UWG_SKill과 플레이어에 전달 
	_UIOwner->AcquireSkill(_skillData->_skillId, _skillData);
}

void UWG_Skill_List::RemoveSkill()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill List Remove Skill"));

}
