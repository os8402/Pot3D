// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "GI_GmInst.generated.h"


USTRUCT()
struct FStatData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _job;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _minAtk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _maxAtk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _defence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _resilience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _dexterity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _intelligence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _luck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _maxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _maxMp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _maxExp;


};


USTRUCT()
struct FRewardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _itemId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _probability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _count;


};

USTRUCT()
struct FDropItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRewardData> _dropItemLists;

};


USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText _name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText _description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatData _statData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _isConsumable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERarity _rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemTypes _itemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _iconPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _meshPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector _dropPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _scale;
};


USTRUCT()
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString _name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatData _statData;

};

UCLASS()
class POT3D_API UGI_GmInst : public UGameInstance
{
	GENERATED_BODY()

public:

	UGI_GmInst();

	virtual void Init() override;

	template<typename T>
	T* GetTableData(ETableDatas type, int32 id);

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

	//UPROPERTY()
	//class UDataTable* _statData;
	UPROPERTY()
	class UDataTable* _dropRewardData;
	UPROPERTY()
	class UDataTable* _itemData;
	UPROPERTY()
	class UDataTable* _unitData;
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


private:
	int32 _gold = 0;

};
template<typename T>
T* UGI_GmInst::GetTableData(ETableDatas type, int32 id)
{
	return _tableLists[(int8)type]->FindRow<T>(*FString::FromInt(id), TEXT(""));
}


