// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/UNIT_Monster.h"
#include "Item/ACT_DropItem.h"
#include "Item/OBJ_Item.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Manager/GI_GmInst.h"
#include "UI/WG_HpBar.h"
#include "Stat/ACP_StatMonster.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

AUNIT_Monster::AUNIT_Monster()
{
	_PSPR_MinimapIcon->SetSpriteColor(FLinearColor::Red);

	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));


}

void AUNIT_Monster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto hpBarWidget = Cast<UWG_HpBar>(_WG_HpBar->GetUserWidgetObject());

	if (hpBarWidget)
	{
		FString chrName = TEXT("유령 기사");
		FString barInfoStr = FString::Printf(TEXT("%s LV %d"), *chrName, 1);
		hpBarWidget->BindHp(_ACP_Stat, FText::FromString(barInfoStr));
	}
}

void AUNIT_Monster::Tick(float DeltaTime)
{

}

void AUNIT_Monster::DeadUnit()
{
	Super::DeadUnit();
	//아이템 드랍
	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gmInst)
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster ID : %d"), GetCharacterId());
		
		auto monsterData = gmInst->GetTableData<FMonsterData>(ETableDatas::MONSTER, GetCharacterId() % 100);
		TArray<int32> rewardIdList;

		if (monsterData)
		{

			int32 rand = FMath::RandRange(0, 101);
			int32 sum = 0;

			for (auto& item : monsterData->_dropItemLists)
			{
				sum += item._probability;

				if (sum <= rand)
				{
					//처음은 무조건 골드
					sum = 0;
					rewardIdList.Add(item._itemId);
				}
				
			}

			TMap<FVector2D, bool> randPosList;
			FVector2D randPos;

			for (auto& id : rewardIdList)
			{
				//TODO : Get Item Info
				UOBJ_Item* newItem = nullptr;
				NewObject<UOBJ_Item>(newItem);
				
				newItem->SetItemInfo(id);


				//TODO : Drop Item Actor
				while (randPosList.Find(randPos) == false)
				{
					randPos = FMath::RandPointInCircle(10.f);
				}

				randPosList.Add(randPos, true);

			
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;

				FVector spawnPos = GetActorLocation();
				FRotator spawnRot = GetActorRotation();

				auto dropItem = Cast<AACT_DropItem>(
					GetWorld()->SpawnActor<AActor>(_ACT_DmgText, spawnPos, spawnRot, spawnParams));

				dropItem->CreateItem(newItem, FVector(randPos.X, randPos.Y , spawnPos.Z));
			
			}
		}
	}

	
}

