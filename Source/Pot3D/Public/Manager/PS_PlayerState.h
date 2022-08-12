#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
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
	void SetGold(int32 gold) {_gold += gold; SavePlayerData();}

	int32 GetCurrentHP() {return _currentHp;}
	int32 GetCurrentMP() {return _currentMp;}
	int32 GetCurrentExp() {return _currentExp;}
	int32 GetGold() {return _gold;}


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
	FStatData _statData;

};
