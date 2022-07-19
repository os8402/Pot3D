#include "UI/WG_MainBar_Slot.h"

void UWG_MainBar_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();

	_MID_coolTime =  _IMG_CoolTime->GetDynamicMaterial();

	if(_MID_coolTime)
		_MID_coolTime->SetScalarParameterValue(TEXT("Percent") , _coolTimePercent);
	
	

}

void UWG_MainBar_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UWG_MainBar_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return true;
}

FReply UWG_MainBar_Slot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return reply.NativeReply;
}

void UWG_MainBar_Slot::RefreshUI()
{
	_TB_SlotIndex->SetText(UtilsLib::ConvertToFText(_slotNum));
}

