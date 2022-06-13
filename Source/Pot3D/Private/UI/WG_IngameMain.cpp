// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_IngameMain.h"
#include "Stat/ACP_StatInfo.h"
#include "UI/WG_GlassBallBar.h"
#include "UI/WG_NamePlate.h"
#include "UI/WG_Inventory.h"
#include "UI/WG_Status.h"


#include <Components/ProgressBar.h>

void UWG_IngameMain::BindStat(class UACP_StatInfo* statComp)
{
	_currentStatComp = statComp;
	_currentStatComp->GetOnHpChanged().AddUObject(this, &UWG_IngameMain::UpdateHp);
}

void UWG_IngameMain::BindCreatureInfo()
{

	//

	_WBP_NamePlate_1->SetVisibility(ESlateVisibility::Hidden);



}

void UWG_IngameMain::UpdateHp()
{
	if (_currentStatComp.IsValid())
	{
	//	_PB_HpMainBar->SetPercent(_currentStatComp->GetHpRatio());
	//	_PB_MonsterInfoHpBar->SetPercent(_currentStatComp->GetHpRatio());
	//	float rand = FMath::RandRange(0.f, 1.f);
	//	_GB_HpBar->SetProgessBar(rand);
	}
	
}

void UWG_IngameMain::OpenInventory()
{
	ESlateVisibility visible = _WBP_Inventory->GetVisibility();
	bool open = false;

	open = (visible == ESlateVisibility::Hidden) ? false : true;
	
	if(open == false)
		_WBP_Inventory->SetVisibility(ESlateVisibility::Visible);
	else
		_WBP_Inventory->SetVisibility(ESlateVisibility::Hidden);

	//TODO : ½ºÅÈ °»½Å 

	//if (_currentStatComp.IsValid())
	//{
		//_WBP_Inventory->GetStatus()->RefreshStat(_currentStatComp.Get());
	//}

	_WBP_Inventory->RefreshInventory();

}
