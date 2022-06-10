#include "Equipment/ACP_Equipment.h"

#include <Components/AudioComponent.h>
#include <Sound/SoundCue.h>

#include "Item/OBJ_Item.h"
#include "Creature/UNIT_Character.h"
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

void UACP_Equipment::SetEquipItem(UOBJ_Item* item)
{
	_currentItem = item;
	_currentOwner->GetStatComp()->RefreshStat();
}