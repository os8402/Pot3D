// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_IngameMain.h"
#include "Stat/ACP_StatInfo.h"
#include "UI/WG_GlassBallBar.h"
#include "UI/WG_NamePlate.h"
#include "UI/WG_Inventory.h"
#include "UI/WG_Status.h"
#include "UI/WG_MainBar.h"
#include "UI/WG_Skill.h"


#include <Components/ProgressBar.h>

void UWG_IngameMain::NativePreConstruct()
{
	Super::NativePreConstruct();

	_WBP_MainBar->SetUIOwner(this);
	_WBP_Skill->SetUIOwner(this);
}

void UWG_IngameMain::BindCreatureInfo()
{
	_WBP_NamePlate_1->SetVisibility(ESlateVisibility::Hidden);
}

void UWG_IngameMain::CheckWidgetVisibilty(UUserWidget* widget)
{
	ESlateVisibility visible = widget->GetVisibility();
	bool open = false;

	open = (visible == ESlateVisibility::Hidden) ? false : true;

	if (open == false)
		widget->SetVisibility(ESlateVisibility::Visible);
	else
		widget->SetVisibility(ESlateVisibility::Hidden);

}

void UWG_IngameMain::OpenInventory()
{
	CheckWidgetVisibilty(_WBP_Inventory);

	_WBP_Inventory->RefreshInventory();

}

void UWG_IngameMain::OpenSkill()
{
	CheckWidgetVisibilty(_WBP_Skill);

}
