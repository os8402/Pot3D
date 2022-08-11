// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/GameDataTable.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "GI_GmInst.generated.h"



UCLASS()
class POT3D_API UGI_GmInst : public UGameInstance
{
	GENERATED_BODY()

public:

	UGI_GmInst();

	virtual void Init() override;

	template<typename T>
	T* GetTableData(ETableDatas type, int32 id);
	template<typename T>
	T* GetTableData(ETableDatas type, FString name);

	void RespawnMonster();
	void DestoryMonster(int32 id);

	int32 GetTotalMonsterCount() { return _totalMonsterCount; }
	int32 GetKeyMonsterCount() { return _keyMonsterCount; }

	void RespawnPlayer(class AUNIT_PlayerCT* ct);
	void DestroyPlayer(int32 id);

	int32 GenerateKey(int32 totalCount);
	void AddKeyPlayerCount(class AUNIT_Player* player);

	int32 GetTotalPlayerCount() { return _totalPlayerCount; }
	int32 GetKeyPlayerCount() { return _keyPlayerCount; }
	


private:


	UPROPERTY()
	class UDataTable* _dropRewardData;
	UPROPERTY()
	class UDataTable* _itemData;
	UPROPERTY()
	class UDataTable* _unitData;
	UPROPERTY()
	class UDataTable* _skillData;
	UPROPERTY()
	class UDataTable* _mapData;
	UPROPERTY()
	TArray<UDataTable*> _tableLists;

private:

	//Player
	int32 _totalPlayerCount = 0;
	int32 _keyPlayerCount = 1;
	
	UPROPERTY(VisibleAnywhere , Category ="Pawn")
	TSubclassOf<class AUNIT_Player> _spawnPlayer;

	UPROPERTY(VisibleAnywhere, Category="Pawn")
	TMap<int32 , class AUNIT_Player*> _playerLists;

private: 
	//Player
	int32 _totalMonsterCount = 0;
	int32 _keyMonsterCount = 1;

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	TSubclassOf<class AUNIT_Monster> _spawnMonster;

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	TMap<int32, class AUNIT_Monster*> _monsterLists;

private:

	FTimerHandle _respawnTimer;


public:
	void SetGold(int32 gold)
	{
		//TODO : 그 외 보안 처리 다 들어가지만 포폴이라 안 함
		_gold += gold;

	}

	int32 GetGold() { return _gold; }
	TArray<FSkillData*> GetSkillDatas() {return _skillDatas;}


private:
	int32 _gold = 0;

	TArray<FSkillData*> _skillDatas;

	
};

template<typename T>
T* UGI_GmInst::GetTableData(ETableDatas type, int32 id)
{
	return _tableLists[(int8)type]->FindRow<T>(*FString::FromInt(id), TEXT(""));
}

template<typename T>
T* UGI_GmInst::GetTableData(ETableDatas type, FString name)
{
	return _tableLists[(int8)type]->FindRow<T>(*name , TEXT(""));
}

