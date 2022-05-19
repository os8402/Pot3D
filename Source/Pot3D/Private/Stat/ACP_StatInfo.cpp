// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/ACP_StatInfo.h"
#include "Manager/GI_GmInst.h"
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
			_maxHp = unitData->_statData._maxHp;
			SetHp(unitData->_statData._maxHp);
			_attack = unitData->_statData._attack;
			_maxMp = unitData->_statData._maxMp;
			SetMp(unitData->_statData._maxMp);
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

