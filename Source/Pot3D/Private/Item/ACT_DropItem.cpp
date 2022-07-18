// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ACT_DropItem.h"
#include "Item/OBJ_Item.h"
#include "Controller/UNIT_PlayerCT.h"
#include "Creature/UNIT_Player.h"
#include "UI/WG_IngameMain.h"
#include "UI/WG_DropItemInfo.h"
#include "UI/WG_Inventory.h"

#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>
#include <Sound/SoundCue.h>

// Sets default values
AACT_DropItem::AACT_DropItem()
{
	USceneComponent* defalutRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT_COMP"));

	RootComponent = defalutRoot;

	_BOX_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	_BOX_Trigger->SetCollisionProfileName(TEXT("DropItem"));
	_MESH_Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	_MESH_Comp->SetCollisionProfileName(TEXT("DropItem"));

	_BOX_Trigger->SetupAttachment(RootComponent);

	_MESH_Comp->SetupAttachment(_BOX_Trigger);

	_WC_Info = CreateDefaultSubobject<UWidgetComponent>(TEXT("ITEM_INFO"));
	_WC_Info->SetupAttachment(_BOX_Trigger);
	_WC_Info->SetWidgetSpace(EWidgetSpace::Screen);
	_WC_Info->SetWorldLocation(FVector(0, 0 , 100));


	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_DropItemInfo.WBP_DropItemInfo_C'"));
	if (UW.Succeeded())
	{
		_WC_Info->SetWidgetClass(UW.Class);
		_WC_Info->SetDrawSize(FVector2D(150.f, 25.f));
	}

	PrimaryActorTick.bCanEverTick = true;

}



void AACT_DropItem::Tick(float DeltaSeconds)
{
	
	Super::Tick(DeltaSeconds);

	if (_bFlotting)
	{
		_MESH_Comp->AddForce(FVector::UpVector * _upforce);
		_MESH_Comp->AddAngularImpulse(FVector::LeftVector * (_rotforce));
	}
	

	_timeDestroy += DeltaSeconds;

	if (_timeDestroy > 0.1f && _bFlotting)
	{
		_bFlotting = false; 

		_MESH_Comp->SetEnableGravity(true);

	}
	

	if (_timeDestroy > 20.f)
	{
		//Destroy();
	}
}

void AACT_DropItem::BeginPlay()
{
	Super::BeginPlay();

}

void AACT_DropItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_WC_Info->InitWidget();
	_WC_Info->SetVisibility(false);


	_MESH_Comp->SetSimulatePhysics(true);
	_MESH_Comp->OnComponentHit.AddDynamic(this, &AACT_DropItem::OnPlaneHit);

	_BOX_Trigger->SetSimulatePhysics(true);
	_BOX_Trigger->SetEnableGravity(true);

	_timeDestroy = 0;

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

	// UI µî·Ï

	auto infoWidget = Cast<UWG_DropItemInfo>(_WC_Info->GetUserWidgetObject());
	infoWidget->BindItemInfo(_dropItem);

	_WG_DropInfo = infoWidget;

	_WC_Info->SetRelativeLocation(FVector(0.f, 0.f, 200.f));


}


void AACT_DropItem::OnPlaneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherComponent->GetCollisionProfileName() == TEXT("DropItem"))
		return;

	if(HitComponent == _BOX_Trigger)
		return;

	FString str = FString::Printf(TEXT("%s : Hit World Static -> %s") , *HitComponent->GetName(),  *OtherActor->GetName());

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);
	
	_WC_Info->SetVisibility(true);

	FRotator newRot = FRotator(0, 0, 0);

	_BOX_Trigger->SetRelativeRotation(newRot);
	
	if(_dropItem->GetItemId() != 10001)
		newRot = FRotator(0 , 0 , -90.f);
	

	FQuat quatRot = FQuat(newRot);
	_MESH_Comp->SetWorldRotation(quatRot);

	_BOX_Trigger->SetSimulatePhysics(false);
	_MESH_Comp->SetSimulatePhysics(false);

	_MESH_Comp->SetRelativeLocation(_BOX_Trigger->GetRelativeLocation());


}

void AACT_DropItem::SetPickUpMesh()
{
	UStaticMesh* newMesh = Cast<UStaticMesh>(
		StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *_dropItem->GetMeshPath().ToString()));

	if (newMesh)
	{
		_MESH_Pickup = newMesh;
		_MESH_Comp->SetRelativeScale3D(FVector::OneVector * _dropItem->GetScale());
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
