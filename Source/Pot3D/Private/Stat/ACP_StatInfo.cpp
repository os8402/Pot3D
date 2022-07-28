#include "Stat/ACP_StatInfo.h"
#include "Item/OBJ_Item.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UACP_StatInfo::UACP_StatInfo()
{

	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	//TODO : DB에서 불러와야함
}


void UACP_StatInfo::InitializeComponent()
{
	Super::InitializeComponent();

	//보너스 스탯 초기화
	for (int i = 0; i < (int32)EStatTypes::END; i++)
	{
		_bonusStats.Add(i, 0);
	}

}

void UACP_StatInfo::OnAttacked(int32 dmg)
{
	int32 newHp = _hp - dmg;
	SetHp(newHp);
}


void UACP_StatInfo::SetCharacterId(int32 id)
{
	_chrId = id;

	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gmInst)
	{
		auto unitData = gmInst->GetTableData<FUnitData>(ETableDatas::UNIT, _chrId);


		if (unitData)
		{
			_level = unitData->_statData._level;
			_chrName = unitData->_name;
			_job = unitData->_statData._job;
			_unitType = unitData->_type;
			_maxHp = unitData->_statData._maxHp;
			SetHp(unitData->_statData._maxHp);
			_maxMp = unitData->_statData._maxMp;
			SetMp(unitData->_statData._maxMp);

			_minAtk = unitData->_statData._minAtk;
			_maxAtk = unitData->_statData._maxAtk;
			_defence = unitData->_statData._defence;
			_resilience = unitData->_statData._resilience;
			_strength = unitData->_statData._strength;
			_dexterity = unitData->_statData._dexterity;
			_intelligence = unitData->_statData._intelligence;
			_luck = unitData->_statData._luck;
		}

	}
}

void UACP_StatInfo::SetHp(int32 newHp)
{
	_hp = FMath::Max(0, newHp);

	if (_hp <= 0)
		_onUnitDied.Broadcast();

	_onHpChanged.Broadcast();
}

void UACP_StatInfo::SetMp(int32 newMp)
{
	_mp = FMath::Max(0, newMp);

	_onMpChanged.Broadcast();
}

void UACP_StatInfo::SetExp(int32 exp)
{
	
}

void UACP_StatInfo::RefreshStat(const FStatData statData, const TMap<int32, int32> bonusStats)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Refresh Stat"));

	_maxHp += statData._maxHp;
	_maxMp += statData._maxMp;
	_minAtk += statData._minAtk;
	_maxAtk += statData._maxAtk;
	_defence += statData._defence;
	_resilience += statData._resilience;
	_strength += statData._strength;
	_dexterity += statData._dexterity;
	_intelligence += statData._intelligence;
	_luck += statData._luck;

	for (auto& stat : bonusStats)
	{
		_bonusStats[stat.Key] += stat.Value;
	}
	
	_bonusMinAtk += statData._minAtk;
	_bonusMaxAtk += statData._maxAtk;
	_bonusDef += statData._defence;
	_bonusRes += statData._resilience;

}

