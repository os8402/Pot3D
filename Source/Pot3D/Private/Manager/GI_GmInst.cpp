// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GI_GmInst.h"
#include "Creature/UNIT_Monster.h"
#include "Creature/UNIT_Player.h"
#include "Controller/UNIT_PlayerCT.h"

UGI_GmInst::UGI_GmInst()
{
	//static ConstructorHelpers::FObjectFinder<UDataTable> StatData(TEXT("DataTable'/Game/Resources/Data/StatDataTable.StatDataTable'"));
	//if (StatData.Succeeded())
	//	_statData = StatData.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterData(TEXT("DataTable'/Game/Resources/Data/MonsterDataTable.MonsterDataTable'"));
	if (MonsterData.Succeeded())
		_monsterData = MonsterData.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemData(TEXT("DataTable'/Game/Resources/Data/ItemDataTable.ItemDataTable'"));
	if (ItemData.Succeeded())
		_itemData = ItemData.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> UnitData(TEXT("DataTable'/Game/Resources/Data/UnitDataTable.UnitDataTable'"));
	if (UnitData.Succeeded())
		_unitData = UnitData.Object;


	//테이블에 넣는 서순주의 
	_tableLists.Add(_unitData);
	_tableLists.Add(_monsterData);
	_tableLists.Add(_itemData);


	
	static ConstructorHelpers::FClassFinder<AUNIT_Monster> EM(TEXT("Blueprint'/Game/BluePrints/Monster/001/BP_001_UnitMonster.BP_001_UnitMonster_C'"));
	if (EM.Succeeded())
		_spawnMonster = EM.Class;

	static ConstructorHelpers::FClassFinder<AUNIT_Player> EP(TEXT("Blueprint'/Game/BluePrints/Player/BP_UnitPlayer.BP_UnitPlayer_C'"));
	if (EP.Succeeded())
		_spawnPlayer = EP.Class;
}


void UGI_GmInst::Init()
{
	Super::Init();

	GetWorld()->GetTimerManager().SetTimer(_respawnTimer, this, &UGI_GmInst::RespawnMonster, 4.f, true);
}

void UGI_GmInst::RespawnMonster()
{
	if (_totalMonsterCount < 5)
	{
		_totalMonsterCount++;
		FActorSpawnParameters spawnParams;

		int32 x = FMath::RandRange(-800.f , 800.f);
		int32 y = FMath::RandRange(-800.f , 800.f);
		FVector spawnLoc = FVector(x, y, 120.f);
		FRotator spawnRot = FRotator(FQuat::Identity);

		auto respawnMonster = Cast<AUNIT_Monster>
			(GetWorld()->SpawnActor<AActor>(_spawnMonster, spawnLoc, spawnRot, spawnParams));

		if (respawnMonster == nullptr)
			return;

		int32 _chrID = FMath::RandRange(1,3);
	


		int32 key = GenerateKey(_keyMonsterCount);
		respawnMonster->SetConnectedId(key);

		_monsterLists.Add(_keyMonsterCount, respawnMonster);

		_keyMonsterCount++;


	}

}

void UGI_GmInst::DestoryMonster(int32 id)
{
	int key = id >> 24;
	GetWorld()->DestroyActor(_monsterLists[key]);
	--_totalMonsterCount;
}

void UGI_GmInst::RespawnPlayer(class AUNIT_PlayerCT* ct)
{
	_totalPlayerCount++;
	FActorSpawnParameters spawnParams;
	int32 x = FMath::RandRange(-800, 800);
	int32 y = FMath::RandRange(-800, 800);
	FVector spawnLoc = FVector(x, y, 120.f);
	FRotator spawnRot = FRotator(FQuat::Identity);

	auto respawnPlayer = Cast<AUNIT_Player>(
		GetWorld()->SpawnActor<AActor>(_spawnPlayer, spawnLoc, spawnRot, spawnParams));

	if (ct)
		ct->OnPossess(respawnPlayer);

	AddKeyPlayerCount(respawnPlayer);
}

void UGI_GmInst::DestroyPlayer(int32 id)
{
	int key = id >> 24;
	GetWorld()->DestroyActor(_playerLists[key]);
	_totalPlayerCount--;
}

int32 UGI_GmInst::GenerateKey(int32 totalCount)
{
	return totalCount << 24;
}

void UGI_GmInst::AddKeyPlayerCount(class AUNIT_Player* player)
{
	_playerLists.Add(_keyPlayerCount, player);
	_keyPlayerCount++;
}

