// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Status.h"

#include <Components/TextBlock.h>

#include "Stat/ACP_StatInfo.h"

void UWG_Status::RefreshStat(class UACP_StatInfo* statComp)
{

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Refrsh UI STAT"));
	FText lv = UtilsLib::ConvertToFText(statComp->GetLevel());
	FText str = UtilsLib::ConvertToFText(statComp->GetStrength());
	FText dex = UtilsLib::ConvertToFText(statComp->GetDexterity());
	FText intel = UtilsLib::ConvertToFText(statComp->GetIntelligence());
	FText luk = UtilsLib::ConvertToFText(statComp->GetLuck());
	FText atk = UtilsLib::ConvertToFText(statComp->GetMinAttack() , statComp->GetMaxAttack());
	FText def = UtilsLib::ConvertToFText(statComp->GetDefence());
	FText res = UtilsLib::ConvertToFText(statComp->GetResilience());


	_TB_Stat_Lv->SetText(lv);
	_TB_Stat_Str->SetText(str);
	_TB_Stat_Dex->SetText(dex);
	_TB_Stat_Int->SetText(intel);
	_TB_Stat_Luk->SetText(luk);
	_TB_Stat_Atk->SetText(atk);
	_TB_Stat_Def->SetText(def);
	_TB_Stat_Res->SetText(res);

}
