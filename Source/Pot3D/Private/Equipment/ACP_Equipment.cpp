#include "Equipment/ACP_Equipment.h"

#include <Components/AudioComponent.h>
#include <Sound/SoundCue.h>

#include "Creature/UNIT_Character.h"

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

// Called when the game starts
void UACP_Equipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


