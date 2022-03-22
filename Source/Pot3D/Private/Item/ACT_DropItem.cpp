// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ACT_DropItem.h"
#include "Item/OBJ_Item.h"
#include "UI/WG_DropItemInfo.h"
#include <Components/WidgetComponent.h>

// Sets default values
AACT_DropItem::AACT_DropItem()
{
	USceneComponent* defalutRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT_COMP"));

	RootComponent = defalutRoot;

	_MESH_Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	_MESH_Comp->SetupAttachment(RootComponent);

	_WG_Info = CreateDefaultSubobject<UWidgetComponent>(TEXT("ITEM_INFO"));
	_WG_Info->SetupAttachment(defalutRoot);


	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_DropItemInfo.WBP_DropItemInfo_C'"));
	if (UW.Succeeded())
	{
		_WG_Info->SetWidgetClass(UW.Class);
		_WG_Info->SetDrawSize(FVector2D(200.f, 50.f));
	}

}

void AACT_DropItem::PostInitializeComponents()
{
	_WG_Info->InitWidget();
}

void AACT_DropItem::CreateItem(UOBJ_Item* newItem , FVector dropPos)
{
	//ASSERT(newItem == nullptr);
	if (newItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Item is Failed"));
		return;
	}
	_item = newItem;

	_MESH_Comp->SetStaticMesh(_item->GetPickUpMesh());
	_MESH_Comp->SetRelativeLocation(dropPos);


	auto infoWidget = Cast<UWG_DropItemInfo>(_WG_Info->GetUserWidgetObject());
	infoWidget->UpdateText(_item->GetItemName());
	
	_WG_Info->SetRelativeLocation(FVector(0.f, 0.f, 200.f));


}

