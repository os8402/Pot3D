#include "UI/WG_Buff.h"
#include "UI/WG_MainBar.h"
#include <Components/Border.h>

void UWG_Buff::NativePreConstruct()
{

}

void UWG_Buff::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);


	if (_BD_Border->IsHovered() && _uiOwner)
	{
		_uiOwner->ChangeTooltip(_toolTipText);
	}


}

void UWG_Buff::RefreshUI(int32 value, EBuffTypes buffType)
{
	_buffType = buffType;
	UTexture2D* newTexture = nullptr;
	FLinearColor iconColor;

	FString toolTipStr;

	switch (buffType)
	{

	case EBuffTypes::HP:
		iconColor = FLinearColor(0.17f, 0.51f, 0.5f);
		UtilsLib::GetAssetDynamic(&newTexture, TEXT("Texture2D'/Game/Resources/fantasy_gui_4/textures/icons/silver/fg4_iconsSilver_heart.fg4_iconsSilver_heart'"));
		toolTipStr = FString::Printf(TEXT("체력 +%d"), value);
		break;
	case EBuffTypes::MP:
		break;
	case EBuffTypes::RESILIENCE:
		iconColor = FLinearColor(1.f, 0.25f, 0.2f);
		UtilsLib::GetAssetDynamic(&newTexture, TEXT("Texture2D'/Game/Resources/fantasy_gui_4/textures/icons/items/fg4_icons_fire.fg4_icons_fire'"));
		toolTipStr = FString::Printf(TEXT("회복력 +%d"), value);
		break;
	case EBuffTypes::ATTACK_SPEED:
		break;
	case EBuffTypes::MOVE_SPEED:
		break;
	case EBuffTypes::STRENGH:
		iconColor = FLinearColor(1.f, 0.2f , 3.3f);
		UtilsLib::GetAssetDynamic(&newTexture, TEXT("Texture2D'/Game/Resources/fantasy_gui_4/textures/icons/items/fg4_icons_firesword.fg4_icons_firesword'"));
		toolTipStr = FString::Printf(TEXT("힘 +%d"), value);
		break;
	case EBuffTypes::DEXTERITY:
		break;
	case EBuffTypes::INTELIGENCE:
		break;
	case EBuffTypes::LUCK:
		break;

	default:
		break;
	}

	_IMG_ItemIcon->SetBrushFromTexture(newTexture);
	_IMG_ItemIcon->SetColorAndOpacity(iconColor);

	_toolTipText = FText::FromString(toolTipStr);


}
