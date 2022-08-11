#include "Controller/UNIT_SelectCT.h"
#include "UI/WG_Select.h"
#include "Creature/UNIT_Select.h"

AUNIT_SelectCT::AUNIT_SelectCT()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	UtilsLib::GetClass(&_selectUIClass, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_CharacterSelect.WBP_CharacterSelect_C'"));
		
	
}

void AUNIT_SelectCT::BeginPlay()
{
	Super::BeginPlay();

	
	_selectUI = CreateWidget<UWG_Select>(this, _selectUIClass);
	_selectUI->AddToViewport();

	//if (_ingameMainUI)
	//{
	//	_ingameMainUI->GetMainBar()->BindStat(_UP_owned->GetStatComp());
	//	_ingameMainUI->GetInventory()->SetCurrentOwner(_UP_owned);
	//	_ingameMainUI->GetSkillPanel()->SetCurrentOwner(_UP_owned);
	//	_ingameMainUI->GetSkillPanel()->InitializeUI();

	//	//TEST CODE: 
	//	_ingameMainUI->GetMainBar()->TestPreSlot();

	//}
}

void AUNIT_SelectCT::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//FHitResult hitOther;
	//GetHitResultUnderCursor(ECC_GameTraceChannel5, false, hitOther);


	//if (hitOther.bBlockingHit)
	//{
	//	//캐릭터 [ 몬스터, npc = 추후 멀티 추가되면 플레이어도 넣긴 할듯]
	//	auto other = Cast<AUNIT_Select>(hitOther.Actor);
	//	
	//	if (other)
	//	{
	//		
	//	}
	//}

}
