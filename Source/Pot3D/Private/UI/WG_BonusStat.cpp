// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_BonusStat.h"
#include <COmponents/TextBlock.h>


void UWG_BonusStat::SetBonusStatText(FText text , FLinearColor color)
{
	_TB_BonusStat->SetText(text);
	
	_TB_BonusStat->SetColorAndOpacity(color);

}
