
#include "Manager/PS_PlayerState.h"
#include "Data/SG_SaveData.h"

APS_PlayerState::APS_PlayerState()
{
	_saveSlotName = TEXT("Player1");
	_equipmentWeapon = -1;
	_equipmentArmors.Init(-1, (int32)EItemArmorTypes::END);

	for (int i = 0; i < 20; i++)
	{
		_inventorySlots.Add(i, -1);
	}


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
		TMap<int32, int32> acquireSkills = saveGame->_acquireSkills;
		TMap<int32, int32> mainbarSlots = saveGame->_mainbarSlots;
		TMap<int32, int32> inventorySlots = saveGame->_inventorySlots;
		int32 weaponId = saveGame->_equipmentWeapon;
		TArray<int32> armors = saveGame->_equipmentArmors;

		SetCurrentHp(hp);
		SetCurrentMp(mp);
		SetCurrentExp(exp);
		SetGold(gold);	
		SetAcquireSkills(acquireSkills);
		SetMainbarSlots(mainbarSlots);
		SetInventorySlots(inventorySlots);
		SetEquipmentWeapon(weaponId);
		SetEquipmentArmors(armors);

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
	newSaveData->_acquireSkills = GetAcquireSkills();
	newSaveData->_mainbarSlots = GetMainbarSlots();
	newSaveData->_inventorySlots = GetInventorySlots();
	newSaveData->_equipmentWeapon = GetEquipmentWeapon();

	newSaveData->_equipmentArmors = GetEquipmentArmors();


	if (UGameplayStatics::SaveGameToSlot(newSaveData, _saveSlotName, 0))
	{
		UE_LOG(LogTemp , Log , TEXT("Save!"));
	}

}
