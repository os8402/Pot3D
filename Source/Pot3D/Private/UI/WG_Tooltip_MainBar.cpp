#include "UI/WG_Tooltip_MainBar.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "UI/WG_Slot.h"
#include "UI/WG_TitleBar.h"

void UWG_Tooltip_MainBar::SetTooltipFromData(FSkillData* skillData)
{
	if(skillData == nullptr)	
		return;

	FText title = FText::FromString(skillData->_skillNameUI.ToString());
	_WBP_TitleBar->SetTitle(title);

	UTexture2D* newTexture;
	UtilsLib::GetAssetDynamic<UTexture2D>(&newTexture , skillData->_iconPath.ToString());

	_WBP_Slot->SetTextureIcon(newTexture);

	int32 reduceMana = skillData->_reduceMana;
	float coolTime = skillData->_coolTime;

	_TB_Mana->SetText(UtilsLib::ConvertToFText(reduceMana));
	_TB_CoolTime->SetText(UtilsLib::ConvertToFText(coolTime));

	_RTB_Info->SetText(skillData->_skillInfo);


	
}
