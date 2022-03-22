// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_HpBar.h"
#include "Stat/ACP_StatInfo.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWG_HpBar::BindHp(class UACP_StatInfo* statComp, FText name)
{
	_currentStatComp = statComp;
	statComp->GetOnHpChanged().AddUObject(this, &UWG_HpBar::UpdateHp);
	_TB_NameLv->SetText(name);
}

void UWG_HpBar::UpdateHp()
{
	if (_currentStatComp.IsValid())
		_PB_Hpbar->SetPercent(_currentStatComp->GetHpRatio());
}
