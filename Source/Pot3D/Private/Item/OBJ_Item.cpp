// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/OBJ_Item.h"
#include "Manager/GI_GmInst.h"
#include <Kismet/GameplayStatics.h>

UOBJ_Item::UOBJ_Item()
{

}

void UOBJ_Item::SetItemInfo(int32 id)
{
	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gmInst)
	{
		auto itemData = gmInst->GetTableData<FItemData>(ETableDatas::ITEM, id);

		if (itemData)
		{
			_id = itemData->_id;
			_name = itemData->_name;
			_description = itemData->_description;
			_job = itemData->_job;
			_iconPath = itemData->_iconPath;
			_meshPath = itemData->_meshPath;
			SetPickUpMesh(_meshPath);
		}
		
		
	}
}

void UOBJ_Item::SetPickUpMesh(const FName& meshPath)
{
	UStaticMesh* newMesh = Cast<UStaticMesh>(
	StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *meshPath.ToString()));

	if (newMesh)
	{
		_MESH_Pickup = newMesh;
	}
}
