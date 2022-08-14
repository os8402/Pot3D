#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/GameDataTable.h"
#include "UI/WG_Slot.h"
#include "PS_PlayerState.generated.h"


UCLASS()
class POT3D_API APS_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	APS_PlayerState();
	
public:

	void LoadDataFromPlayer();
	void SavePlayerData();

	void SetCurrentHp(int32 newHp) {_currentHp = newHp; SavePlayerData();}
	void SetCurrentMp(int32 newMp) {_currentMp = newMp; SavePlayerData();}
	void SetCurrentExp(int32 newExp) {_currentExp = newExp; SavePlayerData();}
	
	void AddAcquireSkill(int32 id , int32 level) { if(_acquireSkills.Find(id)) return; _acquireSkills.Add(id , level); SavePlayerData();}
	void RemoveAcquireSkill(int32 id) { if (_acquireSkills.Find(id)) _acquireSkills.Remove(id);  SavePlayerData();}
	void SetAcquireSkills(TMap<int32 , int32> acquireSkills) { _acquireSkills = acquireSkills; }

	void AddMainbarSlot(int32 slotId , int32 skillId) {if(_mainbarSlots.Find(slotId)) return; _mainbarSlots.Add(slotId, skillId); SavePlayerData(); }
	void RemoveMainbarSlot(int32 slotId) {if(_mainbarSlots.Find(slotId)) _mainbarSlots.Remove(slotId); SavePlayerData(); }
	void SetMainbarSlots(TMap<int32 , int32> mainbarSlots) { _mainbarSlots = mainbarSlots; }

	void SetInventorySlot(int32 slotId , int32 itemId) { _inventorySlots[slotId] = itemId;  SavePlayerData();  }
	void SetInventorySlots(TMap<int32 ,int32> inventorySlots) { _inventorySlots = inventorySlots;}

	void ChangeInventorySlot(int32 prev , int32 next)
	{
		int32 prevItemId = _inventorySlots[prev];
		int32 nextItemId = _inventorySlots[next];

		_inventorySlots[prev] = nextItemId;
		_inventorySlots[next] = prevItemId;

		SavePlayerData();
	}

	void SetGold(int32 gold) {_gold += gold; SavePlayerData();}

	void SetEquipmentWeapon(int32 itemId) {_equipmentWeapon = itemId; SavePlayerData(); }
	void SetEquipmentArmor(int32 armorId,  int32 itemId) { _equipmentArmors[armorId] = itemId; SavePlayerData();}
	void SetEquipmentArmors(TArray<int32> armors) {_equipmentArmors = armors;}

	int32 GetCurrentHP() {return _currentHp;}
	int32 GetCurrentMP() {return _currentMp;}
	int32 GetCurrentExp() {return _currentExp;}
	TMap<int32, int32> GetAcquireSkills() {return _acquireSkills; }
	TMap<int32, int32> GetMainbarSlots() {return _mainbarSlots; }
	TMap<int32, int32> GetInventorySlots() {return _inventorySlots; }

	int32 GetEquipmentWeapon() { return _equipmentWeapon;}
	int32 GetEquipmentArmor(int32 armorId) { return _equipmentArmors[armorId];}
	TArray<int32> GetEquipmentArmors() { return _equipmentArmors;}

	int32 GetGold() { return _gold; }

private:

	FString _saveSlotName;


	UPROPERTY()
	int32 _currentHp;
	UPROPERTY()
	int32 _currentMp;
	UPROPERTY()
	int32 _currentExp;
	UPROPERTY()
	int32 _gold;
	UPROPERTY()
	TMap<int32, int32> _acquireSkills;

	UPROPERTY()
	TMap<int32, int32> _mainbarSlots;
	UPROPERTY()
	TMap<int32, int32> _inventorySlots;
	UPROPERTY()
	int32 _equipmentWeapon;
	UPROPERTY()
	TArray<int32> _equipmentArmors;
};
