// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_IngameMain.h"
#include "Stat/ACP_StatInfo.h"
#include "UI/WG_GlassBallBar.h"
#include "UI/WG_NamePlate.h"
#include "UI/WG_Inventory.h"
#include "UI/WG_Status.h"
#include "UI/WG_MainBar.h"


#include <Components/ProgressBar.h>

void UWG_IngameMain::BindCreatureInfo()
{
	_WBP_NamePlate_1->SetVisibility(ESlateVisibility::Hidden);
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
