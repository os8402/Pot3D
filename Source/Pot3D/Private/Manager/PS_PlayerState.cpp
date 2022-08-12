
#include "Manager/PS_PlayerState.h"
#include "Data/SG_SaveData.h"

APS_PlayerState::APS_PlayerState()
{
	_currentHp = 0;
	_currentMp = 0;
	_currentExp = 0;
	_gold = 0;
	_saveSlotName = TEXT("Player1");

}

void APS_PlayerState::LoadDataFromPlayer()
{
	USG_SaveData* saveGame = Cast<USG_SaveData>(UGameplayStatics::LoadGameFromSlot(_saveSlotName , 0));
	if (saveGame == nullptr)
	{
		saveGame = GetMutableDefault<USG_SaveData>();
	}
	else
	{
		int32 hp = saveGame->_currentHp;
		int32 mp = saveGame->_currentMp;
		int32 exp = saveGame->_currentExp;
		int32 gold = saveGame->_gold;

		SetCurrentHp(hp);
		SetCurrentMp(mp);
		SetCurrentExp(exp);
		SetGold(gold);

		SavePlayerData();
	}

}

void APS_PlayerState::SavePlayerData()
{
	USG_SaveData* newSaveData = NewObject<USG_SaveData>();
	newSaveData->_currentHp = GetCurrentHP();
	newSaveData->_currentMp = GetCurrentMP();
	newSaveData->_currentExp = GetCurrentExp();
	newSaveData->_gold = GetGold();

	if (UGameplayStatics::SaveGameToSlot(newSaveData, _saveSlotName, 0))
	{
		UE_LOG(LogTemp , Log , TEXT("Save Error!!"));
	}

}
