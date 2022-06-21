// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/OBJ_Item.h"
#include "Item/OBJ_Weapon_Item.h"
#include "Item/OBJ_Armor_Item.h"
#include "Item/OBJ_Consumable_Item.h"

#include "Creature/UNIT_Monster.h"
#include "Item/ACT_DropItem.h"
#include "Manager/GI_GmInst.h"
#include "UI/WG_NamePlateSmall.h"


#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

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

	auto hpBarWidget = Cast<UWG_NamePlateSmall>(_WG_HpBar->GetUserWidgetObject());

	if (hpBarWidget)
	{
	
		hpBarWidget->BindHp(_ACP_Stat);
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
		TArray<UOBJ_Item*> rewardIdList; // 최종 아이템만 담음
	

		if (dropItemData)
		{


			int32 itemNum = FMath::RandRange(2, 5);
			//	itemNum = 1;

			for (int32 i = 0; i < itemNum; i++)
			{

				//정규 분포 

				int32 result = UtilsLib::NormalDistribution(0, 1);

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

				int32 id = possibleItemList[index]._itemId;
				int32 count = possibleItemList[index]._count;

				auto newItemClass = UOBJ_Item::StaticClass();
				UOBJ_Item* newItem= NewObject<UOBJ_Item>(newItemClass);

				auto itemData = gmInst->GetTableData<FItemData>(ETableDatas::ITEM, id);

				if (itemData)
				{
					EItemTypes itemType = itemData->_itemType;
					if (itemType == EItemTypes::WEAPON)
					{
						auto weaponItemClass = UOBJ_Weapon_Item::StaticClass();
						auto weaponItem = NewObject<UOBJ_Weapon_Item>(weaponItemClass);
						newItem = weaponItem;
					}
					else if (itemType == EItemTypes::ARMOR)
					{
						auto armorItemClass = UOBJ_Armor_Item::StaticClass();
						auto armorItem = NewObject<UOBJ_Armor_Item>(armorItemClass);
						newItem = armorItem;
					}
					else if (itemType == EItemTypes::CONSUMABLE)
					{
						auto consumableItemClass = UOBJ_Consumable_Item::StaticClass();
						auto consumableItem = NewObject<UOBJ_Consumable_Item>(consumableItemClass);
						newItem = consumableItem;
					}
					
				}
				//골드는 랜덤으로..
				if (id == 10001)
				{
					count = FMath::RandRange(count - 50 , count + 500);
				}

	
				bool flag = newItem->SetItemInfo(gmInst, id, count);

				if (flag == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Create Item is Failed"));
					return;
				}

				rewardIdList.Add(newItem);

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
				FRotator spawnRot = FRotator(0, 0 , 0);

				FVector dropPos = FVector(spawnPos.X + randPos.X, spawnPos.Y + randPos.Y, spawnPos.Z + 40.f);

				auto dropItem = Cast<AACT_DropItem>(
					gmInst->GetWorld()->SpawnActor<AActor>(_ACT_DropItem, dropPos, spawnRot, spawnParams));

	
				dropItem->CreateItem(item);



			}
		}

		gmInst->DestoryMonster(GetConnectedId());

	}


}

