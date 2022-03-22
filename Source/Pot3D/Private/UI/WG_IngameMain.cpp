// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_IngameMain.h"
#include "Stat/ACP_StatInfo.h"
#include <Components/ProgressBar.h>

void UWG_IngameMain::BindHp(class UACP_StatInfo* statComp)
{
	_currentStatComp = statComp;
	_currentStatComp->GetOnHpChanged().AddUObject(this, &UWG_IngameMain::UpdateHp);

}

void UWG_IngameMain::UpdateHp()
{
	if (_currentStatComp.IsValid())
	{
		_PB_HpMainBar->SetPercent(_currentStatComp->GetHpRatio());
		_PB_MonsterInfoHpBar->SetPercent(_currentStatComp->GetHpRatio());
	}
	
}
