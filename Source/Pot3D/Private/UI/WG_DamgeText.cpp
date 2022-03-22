// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_DamgeText.h"
#include <Components/TextBlock.h>

void UWG_DamgeText::UpdateText(int32 dmg, FLinearColor color)
{
	FString conv = FString::FromInt(dmg);
	_TB_DmgText->SetText(FText::FromString(conv));
	_TB_DmgText->SetColorAndOpacity(FSlateColor(color));

	PlayAnimation(_WA_Fade);
}
