// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_NamePlate.h"

#include "Components/TextBlock.h"

#include "Stat/ACP_StatInfo.h"
#include "UI/WG_ProgressBar.h"

void UWG_NamePlate::BindHp(class UACP_StatInfo* statComp)
{
	_currentStatComp = statComp;
	statComp->GetOnHpChanged().AddUObject(this, &UWG_NamePlate::UpdateHp);

	FString chrName =  statComp->GetChracterName();
	FString chrLv = FString::Printf(TEXT("LV %d"), statComp->GetLevel());

	_TB_CharName->SetText(FText::FromString(chrName));
	_TB_Lv->SetText(FText::FromString(chrLv));

	UpdateHp();
}

void UWG_NamePlate::UpdateHp()
{
	if (_currentStatComp.IsValid())
		WBP_ProgressBar_Percent->SetProgressBar(_currentStatComp->GetHpRatio());
}
