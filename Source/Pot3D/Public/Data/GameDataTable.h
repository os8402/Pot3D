
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "GameDataTable.generated.h"


USTRUCT()
struct FStatData : public FTableRowBase
{
	GENERATED_BODY()

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
	FText _skillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText _skillInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnitJobs _job;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillTypes _skillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillAttackTypes _skillAttackType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _reduceMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _coolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName _iconPath;

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
	EUnitTypes _type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatData _statData;

};

UCLASS()
class POT3D_API UGameDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
