#include "UI/WG_Skill_Slot.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>

void UWG_Skill_Slot::NativePreConstruct()
{
	_TEX_lock = Cast<UTexture2D>(
		StaticLoadObject(UTexture2D::StaticClass(), nullptr, 
		TEXT("Texture2D'/Game/Resources/fantasy_gui_4/textures/icons/brown/fg4_iconsBrown_lockClosed.fg4_iconsBrown_lockClosed'")));
		

	SetSkillIcon(nullptr);

}

void UWG_Skill_Slot::RefreshUI()
{
	Super::RefreshUI();


}

void UWG_Skill_Slot::SetSkillIcon(UTexture2D* texture)
{
	if (texture == nullptr)
	{
		_IMG_Icon->SetBrushFromTexture(_TEX_lock);
		_TB_SkillLv->SetText(FText::FromString(""));
		return;

	}


	_IMG_Icon->SetBrushFromTexture(texture);

}