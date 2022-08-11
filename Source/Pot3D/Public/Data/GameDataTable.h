
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "GameDataTable.generated.h"

USTRUCT()
struct FMapData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _mapName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText _mapNameUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _minimapTexturePath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _dimensions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _zoom;

};


USTRUCT()
struct FStatData : public FTableRowBase
{
	GENERATED_BODY()

	FStatData()
	{
		_level = 0,
		_job = EUnitJobs::NONE;
		_minAtk = 0,
		 _maxAtk = 0;
		_defence = 0,
		_resilience = 0;
		_strength = 0;
		_dexterity = 0;
		_intelligence = 0;
		_luck = 0;
		_maxHp = 0;
		_maxMp = 0;
		_maxExp = 0;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnitJobs _job;
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


USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _skillId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _skillLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _skillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (MultiLine = true))
	FText _skillInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnitJobs _job;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillTypes _skillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ESkillAttackTypes> _skillAttackTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _reduceMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> _values;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _coolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _requestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _iconPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText _skillNameUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ERecoveryTypes> _recoveryTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EBuffTypes> _buffTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _unitSoundPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _vfxSoundPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _vfxEffectPath;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _soundPath;
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
	EUnitTypes _type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatData _statData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> _unitSoundPathList;

};

UCLASS()
class POT3D_API UGameDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
