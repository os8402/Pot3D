#include "Data/OBJ_FootStepSoundList.h"
#include "Sound/SoundBase.h"

class USoundBase* UOBJ_FootStepSoundList::GetSound(FString sSoundName)
{
	for (TMap<FString, USoundBase*>::TIterator it = m_pSoundList.CreateIterator(); it; ++it)
	{
		if (it->Key == sSoundName)
		{
			return it->Value;
		}
	}
	return nullptr;
}
