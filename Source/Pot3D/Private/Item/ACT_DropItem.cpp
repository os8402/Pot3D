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

#include <Components/AudioComponent.h>

AACT_DropItem::AACT_DropItem()
{

	_BOX_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	_BOX_Trigger->SetCollisionProfileName(TEXT("DropItem"));
	_MESH_Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	_MESH_Comp->SetCollisionProfileName(TEXT("DropItem"));

	RootComponent = _BOX_Trigger;

	_MESH_Comp->SetupAttachment(_BOX_Trigger);

	_WC_Info = CreateDefaultSubobject<UWidgetComponent>(TEXT("ITEM_INFO"));
	_WC_Info->SetupAttachment(_BOX_Trigger);
	_WC_Info->SetWidgetSpace(EWidgetSpace::Screen);
	_WC_Info->SetWorldLocation(FVector(0, 0, 100));

	UtilsLib::GetWidgetClass(_WC_Info, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_DropItemInfo.WBP_DropItemInfo_C'"), FVector2D(150.f, 25.f));

	_Audio_Comp = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO_COMP"));
	_Audio_Comp->SetupAttachment(RootComponent);

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


	int32 soundId = (_dropItem->GetItemId() == 10001) ? 0 : 1;

	if (_Audio_Comp)
	{
		_Audio_Comp->SetSound(_dropItemSoundList[soundId]);
		_Audio_Comp->Play(0.f);
	}

	_bEnabledOutline = true;


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

	int32 value = (on) ? 2 : 0;
	FLinearColor color  = (on) ? FLinearColor(1,1,0, 0.4f) : FLinearColor(0, 0, 0, 0.4f);
	
	_MESH_Comp->SetCustomDepthStencilValue(value);
	_WG_DropInfo->LookItem(color);

}
