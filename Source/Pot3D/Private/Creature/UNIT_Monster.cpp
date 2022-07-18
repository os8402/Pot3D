// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/OBJ_Item.h"
#include "Item/OBJ_Weapon_Item.h"
#include "Item/OBJ_Armor_Item.h"
#include "Item/OBJ_Consumable_Item.h"

#include "Creature/UNIT_Monster.h"
#include "Item/ACT_DropItem.h"
#include "Manager/GI_GmInst.h"
#include "UI/WG_NamePlateSmall.h"

#include "Controller/UNIT_MonsterCT.h"

#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

AUNIT_Monster::AUNIT_Monster()
{


	/*_WG_HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_BAR"));
	_WG_HpBar->SetupAttachment(GetMesh());
	_WG_HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	_WG_HpBar->SetRelativeLocation(FVector(0.f, 0.f, _hpZPos));

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_HpBar(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/NamePlate/WBP_NamePlateSmall_1.WBP_NamePlateSmall_1_C'"));

	if (WBP_HpBar.Succeeded())
	{
		_WG_HpBar->SetWidgetClass(WBP_HpBar.Class);
		_WG_HpBar->SetDrawSize(_hpDrawSize);
	}*/


	_PSPR_MinimapIcon->SetSpriteColor(FLinearColor::Red);

	static ConstructorHelpers::FClassFinder<AActor> DIT(TEXT("Blueprint'/Game/BluePrints/Item/BP_DropItemActor.BP_DropItemActor_C'"));

	if (DIT.Succeeded())
		_ACT_DropItem = DIT.Class;

	AIControllerClass = AUNIT_MonsterCT::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void AUNIT_Monster::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	//_WG_HpBar->InitWidget();
	//_WG_HpBar->SetVisibility(false);

	//auto hpBarWidget = Cast<UWG_NamePlateSmall>(_WG_HpBar->GetUserWidgetObject());

	//if (hpBarWidget)
	//{
	//	hpBarWidget->BindHp(_ACP_Stat);
	//}
	//	

}

void AUNIT_Monster::Tick(float DeltaTime)
{

}

void AUNIT_Monster::DeadUnit()
{
	Super::DeadUnit();

	/*GetWorld()->GetTimerManager().ClearTimer(_hpBarTimer);
	_WG_HpBar->SetVisibility(false);*/

	AController* controller = GetController<AController>();

	controller->Destroy();
	
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

				
				FVector dropPos = item->GetDropPos() + FVector(randPos.X , randPos.Y, 0);
				FVector finalPos = spawnPos + dropPos;

				auto dropItem = Cast<AACT_DropItem>(
					gmInst->GetWorld()->SpawnActor<AActor>(_ACT_DropItem, finalPos, spawnRot, spawnParams));

	
				dropItem->CreateItem(item);
			}
		}

		gmInst->DestoryMonster(GetConnectedId());

	}

	//Destroy();

	

}

void AUNIT_Monster::VisibleHpBar()
{
	//GetWorld()->GetTimerManager().ClearTimer(_hpBarTimer);

	//_WG_HpBar->SetVisibility(true);

	//GetWorld()->GetTimerManager().SetTimer(_hpBarTimer, FTimerDelegate::CreateLambda([&]()
	//	{
	//		_WG_HpBar->SetVisibility(false);
	//	}), 1.5f, false);
}

