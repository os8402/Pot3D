// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Status.h"

#include <Components/TextBlock.h>
#include <Components/RichTextBlock.h>

#include "Stat/ACP_StatInfo.h"

void UWG_Status::RefreshStat(class UACP_StatInfo* statComp)
{

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Refrsh UI STAT"));


	TMap<int32, int32> bonustat = statComp->GetBonuStats();



	FText lv = UtilsLib::ConvertToFText(statComp->GetLevel());
	int32* strBonus = bonustat.Find((int32)EStatTypes::STRENGH);
	int32* dexBonus = bonustat.Find((int32)EStatTypes::DEXTERITY);
	int32* intelBonus = bonustat.Find((int32)EStatTypes::INTELIGENCE);
	int32* lukBonus = bonustat.Find((int32)EStatTypes::LUCK);
	
	
	int32 atkMinBonus = statComp->GetBonusMinAttck();
	int32 atkMaxBonus = statComp->GetBonusMaxAttck();
	int32 defBonus = statComp->GetBonusDefece();
	int32 resBonus = statComp->GetBonusResilience();




	FText strText = UtilsLib::IsBonusStat(statComp->GetStrength(), strBonus);
	FText dexText = UtilsLib::IsBonusStat(statComp->GetDexterity() , dexBonus);
	FText intelText = UtilsLib::IsBonusStat(statComp->GetIntelligence(), intelBonus);
	FText lukText = UtilsLib::IsBonusStat(statComp->GetLuck(), lukBonus);
	FText atkText = UtilsLib::IsBonusStat(statComp->GetMinAttack(), statComp->GetMaxAttack() , atkMinBonus , atkMaxBonus);
	FText defText = UtilsLib::IsBonusStat(statComp->GetDefence(), defBonus);
	FText resText = UtilsLib::IsBonusStat(statComp->GetResilience(), resBonus);

	_TB_Stat_Lv->SetText(lv);
	_TB_Stat_Str->SetText(strText);
	_TB_Stat_Dex->SetText(dexText);
	_TB_Stat_Int->SetText(intelText);
	_TB_Stat_Luk->SetText(lukText);
	_TB_Stat_Atk->SetText(atkText);
	_TB_Stat_Def->SetText(defText);
	_TB_Stat_Res->SetText(resText);

}
