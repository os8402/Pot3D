#include "UI/WG_Skill_Slot.h"
#include "UI/WG_Drag.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

void UWG_Skill_Slot::NativePreConstruct()
{
	_TEX_lock = Cast<UTexture2D>(
		StaticLoadObject(UTexture2D::StaticClass(), nullptr, 
		TEXT("Texture2D'/Game/Resources/fantasy_gui_4/textures/icons/brown/fg4_iconsBrown_lockClosed.fg4_iconsBrown_lockClosed'")));
		

	SetSkillIcon(nullptr);

}

void UWG_Skill_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);


	UWG_Drag* dragDropOperation = NewObject<UWG_Drag>();


	dragDropOperation->_widgetRef = this;
	dragDropOperation->_dragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	dragDropOperation->DefaultDragVisual = this;
	dragDropOperation->Pivot = EDragPivot::MouseDown;

	dragDropOperation->SetSlot(this);

	OutOperation = dragDropOperation;

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Dragging"));
}

bool UWG_Skill_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);



	return false;
}

FReply UWG_Skill_Slot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Right Click"));


	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if(_bLocked)
			return reply.NativeReply;


		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}


	return reply.NativeReply;
}

void UWG_Skill_Slot::RefreshUI()
{
	Super::RefreshUI();


}

void UWG_Skill_Slot::SetSkillIcon(UTexture2D* texture)
{
	if (texture == nullptr)
	{
		_IMG_Icon->SetBrushFromTexture(_TEX_lock);
		_TB_SkillLv->SetText(FText::FromString(""));
		return;

	}

	_IMG_Icon->SetBrushFromTexture(texture);

}