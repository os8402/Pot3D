#include "Equipment/ACP_Equipment.h"

#include <Sound/SoundCue.h>

#include "Item/OBJ_Item.h"
#include "Creature/UNIT_Player.h"
#include "Stat/ACP_StatInfo.h"

UACP_Equipment::UACP_Equipment()
{
	PrimaryComponentTick.bCanEverTick = false;

}



void UACP_Equipment::BeginPlay()
{
	Super::BeginPlay();

}

void UACP_Equipment::EquipItem(UOBJ_Item* item)
{
	if(item == nullptr)
		return;

	_currentItem = item;
	_currentOwner->GetStatComp()->RefreshStat(item->GetStatData() , item->GetBonusStats());
	
	
	
}

void UACP_Equipment::UnEquipItem()
{
	FStatData statData = _currentItem->GetStatData();
	
	statData._maxHp = -statData._maxHp;
	statData._maxMp = -statData._maxMp;
	statData._minAtk = -statData._minAtk;
	statData._maxAtk = -statData._maxAtk;
	statData._defence = -statData._defence;
	statData._resilience = -statData._resilience;
	statData._strength = -statData._strength;
	statData._dexterity = -statData._dexterity;
	statData._intelligence = -statData._intelligence;
	statData._luck = -statData._luck;

	TMap<int32, int32> bonusStats = _currentItem->GetBonusStats();

	for (auto& stat : bonusStats)
	{
		stat.Value = -stat.Value;
	}

	_currentItem = nullptr;
	_currentOwner->GetStatComp()->RefreshStat(statData, bonusStats);
}
