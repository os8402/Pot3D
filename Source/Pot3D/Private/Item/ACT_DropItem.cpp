// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ACT_DropItem.h"
#include "UI/WG_DropItemInfo.h"
#include "Manager/GI_GmInst.h"
#include "Creature/UNIT_Player.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>

// Sets default values
AACT_DropItem::AACT_DropItem()
{
	USceneComponent* defalutRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT_COMP"));

	RootComponent = defalutRoot;

	
	_BOX_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	_MESH_Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	
	_BOX_Trigger->SetupAttachment(RootComponent);
	_MESH_Comp->SetupAttachment(_BOX_Trigger);


	_MESH_Comp->SetCollisionProfileName(TEXT("DropMesh"));
	_BOX_Trigger->SetCollisionProfileName(TEXT("DropItem"));
	_BOX_Trigger->SetBoxExtent(FVector(30.f,30.f,30.f));

	_BOX_Trigger->SetGenerateOverlapEvents(true);

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
	_BOX_Trigger->SetSimulatePhysics(true);
	_BOX_Trigger->SetEnableGravity(true);



	_BOX_Trigger->OnComponentBeginOverlap.AddDynamic(this, &AACT_DropItem::OnCharacterOverlap);


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

	auto infoWidget = Cast<UWG_DropItemInfo>(_WG_Info->GetUserWidgetObject());
	infoWidget->BindItemInfo(_name, _count);
	
	_WG_Info->SetRelativeLocation(FVector(0.f, 0.f, 200.f));


}

void AACT_DropItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("overlapped"));

	AUNIT_Player* player = Cast<AUNIT_Player>(OtherActor);

	if (player)
	{
		UE_LOG(LogTemp, Log, TEXT("player check"));

		//TODO : 인벤토리에 넣음


		Destroy();

	}

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