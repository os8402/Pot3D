#include "Equipment/ACP_Equipment.h"

#include <Components/AudioComponent.h>
#include <Sound/SoundCue.h>

#include "Item/OBJ_Item.h"
#include "Creature/UNIT_Player.h"
#include "Stat/ACP_StatInfo.h"

UACP_Equipment::UACP_Equipment()
{
	PrimaryComponentTick.bCanEverTick = false;


	_Audio_Comp = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO_COMP"));
	_Audio_Comp->bIsPaused = true;
	_Audio_Comp->bIsPaused = false;


}

void UACP_Equipment::SoundPlay(int32 index)
{

}

void UACP_Equipment::BeginPlay()
{
	Super::BeginPlay();

}

void UACP_Equipment::EquipItem(UOBJ_Item* item)
{
	_currentItem = item;
	
	auto statComp = _currentOwner->GetStatComp();
	if (statComp)
	{
		//_currentOwner->GetStatComp()->RefreshStat(item->GetStatData());
		statComp->RefreshStat(item->GetStatData());
	}

	
}

void UACP_Equipment::UnEquipItem()
{
	// 스탯 전부 마이너스로
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

	_currentItem = nullptr;
	_currentOwner->GetStatComp()->RefreshStat(statData);
}
