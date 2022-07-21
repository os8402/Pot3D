#include "UI/WG_MainBar_Slot.h"
#include "UI/WG_Skill_Slot.h"
#include "UI/WG_Drag.h"

#include <Blueprint/WidgetBlueprintLibrary.h>

void UWG_MainBar_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();

	_TEX_EmptyIcon = Cast<UTexture2D>(
		StaticLoadObject(UTexture2D::StaticClass(), nullptr,
			TEXT("Texture2D'/Game/Resources/fantasy_gui_4/textures/icons/fg4_empty.fg4_empty'")));


	_MID_coolTime = _IMG_CoolTime->GetDynamicMaterial();

	if(_MID_coolTime)
		_MID_coolTime->SetScalarParameterValue(TEXT("Percent") , GetCoolTimeRatio());
	
	
}

void UWG_MainBar_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
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

bool UWG_MainBar_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Main Slot Drop"));

	UWG_Drag* dragDropOperation = Cast<UWG_Drag>(InOperation);

	if (dragDropOperation)
	{
		//TODO : 슬롯에 스킬 갱신 

		UWG_Skill_Slot* skillSlot = Cast<UWG_Skill_Slot>(dragDropOperation->GetSlot());
		UWG_MainBar_Slot* mainBarSlot = Cast<UWG_MainBar_Slot>(dragDropOperation->GetSlot());

		//스킬 창에서 가져온 경우
		if (skillSlot)
		{
			//ESkillTypes skillType = skillSlot->
			
			SetSlotType(ESlotTypes::SKILL);
			UTexture2D* newTexture = skillSlot->GetTextureIcon();
			SetTextureIcon(newTexture);
			
			FSkillData* skillData = skillSlot->GetSkillData();
			SetConditionToUseSlot(skillData);
			
		}
		//메인 바 슬롯끼리 이동하는 경우
		else if (mainBarSlot)
		{
			SetSlotType(ESlotTypes::SKILL);
			UTexture2D* newTexture = mainBarSlot->GetTextureIcon();
			SetTextureIcon(newTexture);
			
			mainBarSlot->SetTextureIcon(_TEX_EmptyIcon);
			mainBarSlot->SetSlotType(ESlotTypes::NONE);

		}
	
		return true;
	}

	return true;
}

FReply UWG_MainBar_Slot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{

	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{

		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	}


	return reply.NativeReply;
}

void UWG_MainBar_Slot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (_bCoolTimeFlag)
	{
		TickSlotCoolTime(InDeltaTime);
	}

}


void UWG_MainBar_Slot::TickSlotCoolTime(float InDeltaTime)
{
	if (_coolTime <= 0.f)
	{
		_bCoolTimeFlag = false;
		return;
	}	

	_coolTime -= InDeltaTime;

	if(_MID_coolTime)
		_MID_coolTime->SetScalarParameterValue(TEXT("Percent"), GetCoolTimeRatio());
	
}


bool UWG_MainBar_Slot::CanUseSkillEvent(int32 mp)
{
	bool bCan = !(_bCoolTimeFlag);   
	bool bcan = (mp >= _skillData->_coolTime);

	return bCan;
}

void UWG_MainBar_Slot::StartSkillEvent()
{
	_coolTime = _maxCoolTime;

	_bCoolTimeFlag = true;

}

void UWG_MainBar_Slot::RefreshUI()
{
	_TB_SlotIndex->SetText(UtilsLib::ConvertToFText(_slotNum));


	

}

