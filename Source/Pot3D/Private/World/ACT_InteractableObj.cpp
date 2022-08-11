#include "World/ACT_InteractableObj.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>

#include "UI/WG_ObjectInfo.h"

AACT_InteractableObj::AACT_InteractableObj()
{
	PrimaryActorTick.bCanEverTick = false;

	_BOX_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = _BOX_Trigger;

	_WC_Info = CreateDefaultSubobject<UWidgetComponent>(TEXT("ITEM_INFO"));
	_WC_Info->SetupAttachment(_BOX_Trigger);
	_WC_Info->SetWidgetSpace(EWidgetSpace::Screen);

	UtilsLib::GetWidgetClass(_WC_Info, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Info/WBP_ObjectInfo.WBP_ObjectInfo_C'"), FVector2D(250.f, 50.f));

	_ACP_MinimapPoint = CreateDefaultSubobject<UACP_MinimapPoint>(TEXT("Minimap"));
}


void AACT_InteractableObj::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_WC_Info->InitWidget();
	_WC_Info->SetVisibility(false);

	_MESH_Static = UtilsLib::GetComponent<UStaticMeshComponent>(this, TEXT("StaticMesh"));
	_MESH_Skeletal = UtilsLib::GetComponent<USkeletalMeshComponent>(this, TEXT("SkeletalMesh"));


	auto objectInfoUI = Cast<UWG_ObjectInfo>(_WC_Info->GetUserWidgetObject());

	if(objectInfoUI)
		objectInfoUI->LookObject(_objName);

}

void AACT_InteractableObj::SetOutline(bool on)
{
	int32 value = (on) ? 2 : 0;

	if (_MESH_Static)
	{
		_MESH_Static->SetRenderCustomDepth(on);
		_MESH_Static->SetCustomDepthStencilValue(value);
	}
		

	if (_MESH_Skeletal)
	{
		_MESH_Skeletal->SetRenderCustomDepth(on);
		_MESH_Skeletal->SetCustomDepthStencilValue(value);
	}
	
	_WC_Info->SetVisibility(on);


}

void AACT_InteractableObj::ExecuteInteractableMethod()
{
	switch (_interactableType)
	{
	case EInteractable::WARP:
		ExecuteWarp();
		break;
	case EInteractable::UI:
		ExecuteUI();
		break;

	default:
		break;
	}
}

void AACT_InteractableObj::ExecuteWarp()
{
	UGameplayStatics::OpenLevel(GetWorld() , FName(_interactableStr));
}

void AACT_InteractableObj::ExecuteUI()
{

}
