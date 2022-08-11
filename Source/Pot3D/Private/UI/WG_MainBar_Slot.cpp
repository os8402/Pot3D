#include "UI/WG_MainBar_Slot.h"
#include "UI/WG_Skill_Slot.h"
#include "UI/WG_Drag.h"
#include "UI/WG_MainBar.h"
#include <Components/Button.h>
#include <Components/Border.h>

#include <Blueprint/WidgetBlueprintLibrary.h>

void UWG_MainBar_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();

	UtilsLib::GetAssetDynamic(&_TEX_EmptyIcon, TEXT("Texture2D'/Game/Resources/fantasy_gui_4/textures/icons/fg4_empty.fg4_empty'"));

	_MID_coolTime = _IMG_CoolTime->GetDynamicMaterial();

	 UtilsLib::GetTSubClass(&mainSlotClass, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Slot/WBP_MainBar_Slot.WBP_MainBar_Slot_C'"));

	if (_MID_coolTime)
	{
		_MID_coolTime->SetScalarParameterValue(TEXT("Percent"), GetCoolTimeRatio());
	}
		
	_IMG_CoolTime->SetVisibility(ESlateVisibility::Hidden);
	
	
}

void UWG_MainBar_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UWG_Drag* dragDropOperation = NewObject<UWG_Drag>();

	UWG_MainBar_Slot* visualSlot = CreateWidget<UWG_MainBar_Slot>(_UIOwner.Get() , mainSlotClass);

	if (visualSlot)
	{

		visualSlot->SetSlotType(GetSlotType());
		visualSlot->SetSlotNum(GetSlotNum());
		visualSlot->SetTextureIcon(GetTextureIcon());
		visualSlot->SetSkillData(GetSkillData());
	
		visualSlot->RefreshUI();

		dragDropOperation->DefaultDragVisual = visualSlot;

	}


	dragDropOperation->Pivot = EDragPivot::CenterCenter;

	dragDropOperation->SetSlot(this);

	OutOperation = dragDropOperation;

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Dragging"));

}

bool UWG_MainBar_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	this->SetVisibility(ESlateVisibility::Visible);

	FString str = FString::Printf(TEXT("Main Slot Drop : %d") , GetSlotNum());

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, str);


	UWG_Drag* dragDropOperation = Cast<UWG_Drag>(InOperation);

	if (dragDropOperation)
	{
		//TODO : ���Կ� ��ų ���� 

		UWG_Skill_Slot* skillSlot = Cast<UWG_Skill_Slot>(dragDropOperation->GetSlot());
		UWG_MainBar_Slot* mainBarSlot = Cast<UWG_MainBar_Slot>(dragDropOperation->GetSlot());

		//��ų â���� ������ ���
		if (skillSlot)
		{	
			//TODO : ���� ��ų�� ��ϵǾ� �ִ��� ���̵� üũ.
			FSkillData* skillData = skillSlot->GetSkillData();

			UWG_MainBar_Slot* existSlot = _UIOwner->CheckExistSlot(skillData->_skillId);

			//�̹� ��ϵ� ��ų ����
			if (existSlot != nullptr)
			{
				RemoveSlotData(existSlot);
			}

			MoveSlotData(skillSlot);

		}
		//���� �� ���Գ��� �̵��ϴ� ���
		else if (mainBarSlot)
		{
			//���� ��ȣ ������ ����
			if(mainBarSlot->GetSlotNum() == GetSlotNum())
				return true;

		
			MoveSlotData(mainBarSlot);
			RemoveSlotData(mainBarSlot);

			
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
		// ��ų �ߵ�
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{

		if(_slotType == ESlotTypes::NONE)
			return reply.NativeReply;


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
	if (_BD_Border->IsHovered() && _UIOwner.IsValid())
	{
		_UIOwner.Get()->SetSlotTooltipHovered(this);
	}

}


void UWG_MainBar_Slot::RemoveSlotData(UWG_MainBar_Slot* slot)
{
	if (slot)
	{
		//��� ������ ���� ���� ����
		slot->SetTextureIcon(_TEX_EmptyIcon);
		slot->SetSlotType(ESlotTypes::NONE);
		slot->SetConditionToUseSlot(nullptr);
		slot->SetCoolTimeReset();
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

	if(_IMG_CoolTime->GetVisibility() == ESlateVisibility::Hidden)
		_IMG_CoolTime->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

}

void UWG_MainBar_Slot::RefreshUI()
{
	_TB_SlotIndex->SetText(UtilsLib::ConvertToFText(_slotNum));

}


void UWG_MainBar_Slot::MoveSlotData(UWG_Slot* slot)
{
	UTexture2D* newTexture = slot->GetTextureIcon();
	FSkillData* skillData = slot->GetSkillData();

	ESkillTypes skillType = skillData->_skillType;

	if(skillType == ESkillTypes::PASSIVE)
		return;

	SetSlotType(ESlotTypes::SKILL);
	SetTextureIcon(newTexture);
	SetConditionToUseSlot(skillData);
	
	UWG_MainBar_Slot* mainbarSlot = Cast<UWG_MainBar_Slot>(slot);

	if (mainbarSlot)
	{
		//��ų ��� ���̾�����
		bool flag = mainbarSlot->GetCoolTimeFlag();
		if (flag)
		{
			StartSkillEvent();
			//���� ���Կ��� ��Ÿ�� ������
			_coolTime = mainbarSlot->GetCoolTime();
			mainbarSlot->SetCoolTimeReset();


		}
	}
}

