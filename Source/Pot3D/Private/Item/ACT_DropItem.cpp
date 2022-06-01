// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ACT_DropItem.h"
#include "UI/WG_DropItemInfo.h"
#include "Item/OBJ_Item.h"
#include "Controller/UNIT_PlayerCT.h"

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
	_BOX_Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));
	_BOX_Trigger->SetGenerateOverlapEvents(true);

	_WC_Info = CreateDefaultSubobject<UWidgetComponent>(TEXT("ITEM_INFO"));
	_WC_Info->SetupAttachment(_MESH_Comp);
	_WC_Info->SetWidgetSpace(EWidgetSpace::Screen);



	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_DropItemInfo.WBP_DropItemInfo_C'"));
	if (UW.Succeeded())
	{
		_WC_Info->SetWidgetClass(UW.Class);
		_WC_Info->SetDrawSize(FVector2D(150.f, 25.f));
	}

}



void AACT_DropItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_WC_Info->InitWidget();

	_MESH_Comp->SetSimulatePhysics(true);
	_MESH_Comp->SetEnableGravity(true);
	_BOX_Trigger->SetSimulatePhysics(true);
	_BOX_Trigger->SetEnableGravity(true);

	_BOX_Trigger->OnComponentBeginOverlap.AddDynamic(this, &AACT_DropItem::OnCharacterOverlap);


}

void AACT_DropItem::CreateItem(UOBJ_Item* newItem)
{

	if (newItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Drop Item Is Null"));
		return;
	}

	_dropItem = newItem;

	SetPickUpMesh();

	_MESH_Comp->SetStaticMesh(GetPickUpMesh());

	// UI 등록

	auto infoWidget = Cast<UWG_DropItemInfo>(_WC_Info->GetUserWidgetObject());
	infoWidget->BindItemInfo(_dropItem);

	_WG_DropInfo = infoWidget;

	_WC_Info->SetRelativeLocation(FVector(0.f, 0.f, 200.f));


}

void AACT_DropItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("overlapped"));

	AUNIT_Player* player = Cast<AUNIT_Player>(OtherActor);

	if (player)
	{
		UE_LOG(LogTemp, Log, TEXT("player check"));

		//TODO : 인벤토리에 넣음
		auto pc = Cast<AUNIT_PlayerCT>(player->GetController());
		bool flag = pc->AddItem(_dropItem);

		if (flag)
		{
			UE_LOG(LogTemp, Log, TEXT("Pick up Item"));
			Destroy();
		}

	}

}


void AACT_DropItem::SetPickUpMesh()
{
	UStaticMesh* newMesh = Cast<UStaticMesh>(
		StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *_dropItem->GetMeshPath().ToString()));

	if (newMesh)
	{
		_MESH_Pickup = newMesh;
	}
}

void AACT_DropItem::SetOutline(bool on)
{

	_MESH_Comp->SetRenderCustomDepth(on);
	

	if (on)
	{
		_MESH_Comp->SetCustomDepthStencilValue(2);
		_WG_DropInfo->LookItem(FLinearColor(1, 1, 0, 0.4f));
	}
	
	else
	{
		_MESH_Comp->SetCustomDepthStencilValue(0);
		_WG_DropInfo->LookItem(FLinearColor(0,0,0, 0.4f));
	}		
}
