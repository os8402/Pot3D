// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_DropSlot.h"
#include "UI/WG_Drag.h"
#include "Creature/UNIT_Player.h"
#include "UI/WG_ItemSlot.h"
#include "UI/WG_MainBar_Slot.h"
#include "Item/ACT_DropItem.h"
#include "Controller/UNIT_PlayerCT.h"
#include "UI/WG_IngameMain.h"
#include "UI/WG_Inventory.h"


#include <Kismet/GameplayStatics.h>



void UWG_DropSlot::NativeConstruct()
{
	_player = Cast<AUNIT_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if(_player == nullptr)
		return;

	auto pc = Cast<AUNIT_PlayerCT>(_player->GetController());
	if (pc)
	{
		_inventory = pc->GetMainUI()->GetInventory();
	}

}

bool UWG_DropSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("slot Drop"));

	UWG_Drag* dragDropOperation = Cast<UWG_Drag>(InOperation);

	if (dragDropOperation)
	{
	
		
		UWG_ItemSlot* itemSlot = Cast<UWG_ItemSlot>(dragDropOperation->GetSlot());
		UWG_MainBar_Slot* mainBarSlot = Cast<UWG_MainBar_Slot>(dragDropOperation->GetSlot());

		if(itemSlot == nullptr && mainBarSlot == nullptr)
			return false;

		if (itemSlot)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Spawn Item"));
			SpawnItem(itemSlot);
		}
		
		if (mainBarSlot)
		{
			mainBarSlot->RemoveSlotData(mainBarSlot);
			
		}


		ESlotTypes slotType = dragDropOperation->GetSlot()->GetSlotType();

		switch (slotType)
		{
		case ESlotTypes::ITEM:
			_inventory->RemoveItem(itemSlot->GetSlotNum());
			break;
		case ESlotTypes::EQUIPMENT:
			_inventory->UnEquipItem(itemSlot->GetItem(), false);
			break;
		case ESlotTypes::SKILL:
			break;
		default:
			break;
		}

	

		return true;
	}

	return false;
}

void UWG_DropSlot::SpawnItem(UWG_ItemSlot* slot)
{
	FTransform spawnTransform = _player->GetActorTransform();

	FVector2D randPos = FMath::RandPointInCircle(100.f);
	FVector spawnPos = spawnTransform.GetLocation();
	FVector dropPos = FVector(spawnPos.X + randPos.X, spawnPos.Y + randPos.Y, spawnPos.Z + 20.f);

	spawnTransform.SetLocation(dropPos);

	auto dropItem = Cast<AACT_DropItem>(GetWorld()->SpawnActorDeferred<AACT_DropItem>(_ACT_DropItem, spawnTransform));
	dropItem->FinishSpawning(spawnTransform);

	dropItem->CreateItem(slot->GetItem());



}