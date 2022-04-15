// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/UNIT_Monster.h"
#include "Item/ACT_DropItem.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Manager/GI_GmInst.h"
#include "UI/WG_HpBar.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

AUNIT_Monster::AUNIT_Monster()
{
	_PSPR_MinimapIcon->SetSpriteColor(FLinearColor::Red);

	static ConstructorHelpers::FClassFinder<AActor> DIT(TEXT("Blueprint'/Game/BluePrints/Item/BP_DropItemActor.BP_DropItemActor_C'"));

	if (DIT.Succeeded())
		_ACT_DropItem = DIT.Class;



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

		auto dropItemData = gmInst->GetTableData<FDropItemData>(ETableDatas::MONSTER, GetCharacterId() % 100);
		TArray<FRewardData> possibleItemList; // 후보 선별 과정
		TArray<TPair<int32, int32>> rewardIdList; // 최종 아이템만 담음
	

		if (dropItemData)
		{


			int32 itemNum = FMath::RandRange(2, 5);
			//	itemNum = 1;

			for (int32 i = 0; i < itemNum; i++)
			{

				//정규 분포 

				int result = UtilsLib::NormalDistribution(0, 1);

				for (auto& item : dropItemData->_dropItemLists)
				{
					if (item._probability != result)
						continue;

					possibleItemList.Add(item);

				}

				if (possibleItemList.Num() == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Item Count is Zero"));
					return;
				}
				

				int32 index = FMath::RandRange(0, possibleItemList.Num() - 1);

				TPair<int32,int32> itemData;
				itemData.Key = possibleItemList[index]._itemId;
				itemData.Value = possibleItemList[index]._count;

				rewardIdList.Add(itemData);

			}



			//SPAWN

			TMap<FVector2D, bool> randPosList;
			

			for (auto& item : rewardIdList)
			{
				FVector2D randPos;
				//TODO : Drop Item Actor
				while (true)
				{
					randPos = FMath::RandPointInCircle(100.f);

					if (randPosList.Find(randPos) == false)
					{
						randPosList.Add(randPos, true);
						break;

					}
					

				}

				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;

				FVector spawnPos = GetActorLocation();
				FRotator spawnRot = GetActorRotation();

				FVector dropPos = FVector(spawnPos.X + randPos.X, spawnPos.Y + randPos.Y, spawnPos.Z + 200);

				auto dropItem = Cast<AACT_DropItem>(
					gmInst->GetWorld()->SpawnActor<AActor>(_ACT_DropItem, dropPos, spawnRot, spawnParams));

				int32 itemId = item.Key;
				int32 itemCount = item.Value;

				dropItem->CreateItem(itemId , itemCount,  gmInst);

			}
		}

	}


}

