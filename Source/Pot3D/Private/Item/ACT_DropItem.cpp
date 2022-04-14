// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ACT_DropItem.h"
#include "UI/WG_DropItemInfo.h"
#include <Components/WidgetComponent.h>
#include "Manager/GI_GmInst.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AACT_DropItem::AACT_DropItem()
{
	USceneComponent* defalutRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT_COMP"));

	RootComponent = defalutRoot;

	_MESH_Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	_MESH_Comp->SetupAttachment(RootComponent);

	_WG_Info = CreateDefaultSubobject<UWidgetComponent>(TEXT("ITEM_INFO"));
	_WG_Info->SetupAttachment(_MESH_Comp);

	_WG_Info->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_DropItemInfo.WBP_DropItemInfo_C'"));
	if (UW.Succeeded())
	{
		_WG_Info->SetWidgetClass(UW.Class);
		_WG_Info->SetDrawSize(FVector2D(150.f, 25.f));
	}

}



void AACT_DropItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_WG_Info->InitWidget();


	_MESH_Comp->SetSimulatePhysics(true);
	_MESH_Comp->SetEnableGravity(true);
	_MESH_Comp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);


}

void AACT_DropItem::CreateItem(int32 id , int32 count ,UGI_GmInst* gmInst)
{
	
	_gmInst = gmInst;

	bool flag =  SetItemInfo(id,count);

	if (flag == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Item is Failed"));
		return;
	}



	_MESH_Comp->SetStaticMesh(GetPickUpMesh());
	_MESH_Comp->SetRelativeLocation(GetActorLocation());


	auto infoWidget = Cast<UWG_DropItemInfo>(_WG_Info->GetUserWidgetObject());
	infoWidget->BindItemInfo(_name, _count);
	
	_WG_Info->SetRelativeLocation(FVector(0.f, 0.f, 200.f));


}

bool AACT_DropItem::SetItemInfo(int32 id, int32 count)
{

	bool flag = false;

	if (_gmInst)
	{
		auto itemData = _gmInst->GetTableData<FItemData>(ETableDatas::ITEM, id);

		if (itemData)
		{
			_id = itemData->_id;
			_name = itemData->_name;
			_meshPath = itemData->_meshPath;
			_count = count;
			SetPickUpMesh(_meshPath);
			
			flag = true;
		}


	}

	return flag;


}

void AACT_DropItem::SetPickUpMesh(const FName& meshPath)
{
	UStaticMesh* newMesh = Cast<UStaticMesh>(
	StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *meshPath.ToString()));

	if (newMesh)
	{
		_MESH_Pickup = newMesh;
	}
}