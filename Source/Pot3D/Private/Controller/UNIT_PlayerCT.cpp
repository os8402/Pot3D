#include "Controller/UNIT_PlayerCT.h"
#include <Components/WidgetComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework//CharacterMovementComponent.h>
#include <Components/SceneCaptureComponent2D.h>
#include <Camera/CameraShake.h>
#include <Components/CanvasPanel.h>
#include <Engine/PostProcessVolume.h>


#include "Creature/UNIT_Character.h"
#include "Creature/UNIT_Player.h"
#include "Creature/UNIT_Monster.h"

#include "Stat/ACP_StatInfo.h"

#include "Item/ACT_DropItem.h"
#include "Animation/UNIT_Anim.h"

#include "UI/WG_IngameMain.h"
#include "UI/WG_NamePlate.h"
#include "UI/WG_Inventory.h"
#include "UI/WG_MainBar.h"
#include "UI/WG_Skill.h"
#include "UI/WG_MainBar_Slot.h"

#include "Item/OBJ_Item.h"
#include "Item/ACT_DropItem.h"

AUNIT_PlayerCT::AUNIT_PlayerCT()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	_WC_CursorNormal = CreateDefaultSubobject<UWidgetComponent>(TEXT("CURSOR_NORMAL"));
	static ConstructorHelpers::FClassFinder<UUserWidget> CB(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_CursorNormal.WBP_CursorNormal_C'"));

	if (CB.Succeeded())
		_WC_CursorNormal->SetWidgetClass(CB.Class);

	_WC_CursorAttack = CreateDefaultSubobject<UWidgetComponent>(TEXT("CURSOR_ATTACK"));
	static ConstructorHelpers::FClassFinder<UUserWidget> CA(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_CursorAttack.WBP_CursorAttack_C'"));

	if (CA.Succeeded())
		_WC_CursorAttack->SetWidgetClass(CA.Class);


	static ConstructorHelpers::FClassFinder<UMatineeCameraShake> CS_NORMAL_ATK(TEXT("Blueprint'/Game/BluePrints/Camera/BP_CS_NormalAttack.BP_CS_NormalAttack_C'"));
	if (CS_NORMAL_ATK.Succeeded())
		_CS_NormalAttack = CS_NORMAL_ATK.Class;

	
	static ConstructorHelpers::FClassFinder<UWG_IngameMain> WB_Ingame(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_InGameMain.WBP_InGameMain_C'"));
	if (WB_Ingame.Succeeded())
		_ingameMainClass = WB_Ingame.Class;
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MID_MONSTER(TEXT("MaterialInstanceConstant'/Game/Resources/Materials/InteractiveOutline/MI_InteractiveOutline_Monster.MI_InteractiveOutline_Monster'"));
	if(MID_MONSTER.Succeeded())
		_MI_Outlines.Add(MID_MONSTER.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MID_ITEM(TEXT("MaterialInstanceConstant'/Game/Resources/Materials/InteractiveOutline/MI_InteractiveOutline_Item.MI_InteractiveOutline_Item'"));
	if (MID_ITEM.Succeeded())
		_MI_Outlines.Add(MID_ITEM.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MID_NPC(TEXT("MaterialInstanceConstant'/Game/Resources/Materials/InteractiveOutline/MI_InteractiveOutline_Item.MI_InteractiveOutline_Item'"));
	if (MID_NPC.Succeeded())
		_MI_Outlines.Add(MID_NPC.Object);

}

void AUNIT_PlayerCT::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	InitPlayerUnit();
}

void AUNIT_PlayerCT::OnUnPossess()
{
	Super::OnUnPossess();
}

void AUNIT_PlayerCT::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void AUNIT_PlayerCT::BeginPlay()
{
	Super::BeginPlay();

	_UP_owned = Cast<AUNIT_Player>(GetCharacter());

	_ingameMainUI = CreateWidget<UWG_IngameMain>(this, _ingameMainClass);
	_ingameMainUI->AddToViewport();

	if (_ingameMainUI)
	{
		_ingameMainUI->GetMainBar()->BindStat(_UP_owned->GetStatComp());
		_ingameMainUI->GetInventory()->SetCurrentOwner(_UP_owned);
		_ingameMainUI->GetSkillPanel()->SetCurrentOwner(_UP_owned);
		_ingameMainUI->GetSkillPanel()->InitializeUI();

	}

	//TODO : Post process

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(this, APostProcessVolume::StaticClass(), actors);

	if (actors.Num() > 0)
	{
		_ppv = Cast<APostProcessVolume>(actors[0]);

		if (_ppv)
		{

			_MI_PostProcess.Add(_MI_Outlines[0]);

			FPostProcessSettings& postProcessSettings = _ppv->Settings;
			FWeightedBlendable weightBlendable;	
			weightBlendable.Weight = 1;

			for (int32 i = 0; i < _MI_PostProcess.Num(); i++)
			{
				weightBlendable.Object = _MI_PostProcess[i];
				postProcessSettings.WeightedBlendables.Array.Add(weightBlendable);
			}

		}
	}
	
}

void AUNIT_PlayerCT::SetPostProcessOutline(EOutline outline)
{

	FPostProcessSettings& postProcessSettings = _ppv->Settings;

	FWeightedBlendable weightBlendable;
	weightBlendable.Object = _MI_Outlines[(int32)outline];
	weightBlendable.Weight = 1;

	postProcessSettings.WeightedBlendables.Array[(int32)EPostProcess::OUTLINE] = weightBlendable;
	
}

void AUNIT_PlayerCT::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	FHitResult cursorHit;
	GetHitResultUnderCursor(ECC_Visibility, true, cursorHit);
	FVector cursorNormal = cursorHit.ImpactNormal;
	FRotator cursorRot = cursorNormal.Rotation();

	_UP_owned = Cast<AUNIT_Player>(GetCharacter());

	if (_UP_owned)
	{
		EUnitStates state = _UP_owned->GetUnitStates();

		if (state == EUnitStates::DEAD)
			return;

		if (_bClickMouseDown)
			ClickMouseDown();

		if (_bClickMouse)
			ClickMouseCursor();

//==============================================
		if (_bMoving)
			SetMoveDest(_destPos, DeltaTime);

		if (_bAttacking)
			ChaseToEnemy(DeltaTime);
		else if (_bPicking)
			PickUpItem(DeltaTime);


	}

	
}

void AUNIT_PlayerCT::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Move", IE_Pressed, this, &AUNIT_PlayerCT::OnMovePressed);
	InputComponent->BindAction("Move", IE_Released, this, &AUNIT_PlayerCT::OnMoveReleased);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AUNIT_PlayerCT::OpenInventory);
	InputComponent->BindAction("Skill", IE_Pressed, this, &AUNIT_PlayerCT::OpenSkillPanel);
	InputComponent->BindAction("MainBarSlotEvent", IE_Pressed , this , &AUNIT_PlayerCT::MainBarSlotEvent);


}

void AUNIT_PlayerCT::InitPlayerUnit()
{
	_bClickMouse = _bMoving = _bAttacking = false;

	auto unitCharacter = Cast<AUNIT_Character>(GetPawn());
}

void AUNIT_PlayerCT::ClickMouseCursor()
{

	_bClickMouse = true;


	if (_UP_owned == nullptr)
		return;

	if (_UP_owned->IsAttacking())
		return;

	if (_bAttacking || _bPicking)
		return;
		
	
	FHitResult hit;
	GetHitResultUnderCursor(ECC_Pawn, false, hit);


	//UI를 클릭한 경우 리턴
	if (hit.bBlockingHit == false)
		return;

	//이동 목적지
	_destPos = hit.ImpactPoint;


}

void AUNIT_PlayerCT::ClickMouseDown()
{

	if (_UP_owned == nullptr)
		return;

	if (_UP_owned->IsAttacking())
		return;


	_bClickMouseDown = _bMoving =  _bAttacking = _bPicking = false;

	_bMoving = true;


	// 플레이어와 충돌이 일어나는 모든 오브젝트 
	FHitResult objHit;
	GetHitResultUnderCursor(ECC_GameTraceChannel5, false, objHit);

	//아이템 오브젝트
	FHitResult itemHit;
	GetHitResultUnderCursor(ECC_GameTraceChannel3, false, itemHit);

	auto monster = Cast<AUNIT_Monster>(objHit.Actor);
	auto dropItem = Cast<AACT_DropItem>(itemHit.Actor);

	if (monster == nullptr && dropItem == nullptr)
		return;

	//애니메이션 취소
	_UP_owned->GetUnitAnim()->StopAllMontages(.1f);

	if (monster)
	{
		_UP_owned->SetTargetEnemy(monster);
		_bAttacking = true;
	}
	else if (dropItem)
	{
		_bPicking = true;
		_ACT_DropItem = dropItem;
	}

}

void AUNIT_PlayerCT::SetMoveDest(const FVector destPos, float deltaTime)
{
	if (_UP_owned == nullptr)
		return;


	float const dist = FVector::Dist(destPos, _UP_owned->GetActorLocation());

	if (dist > 100.f)
	{
		UCharacterMovementComponent* movementComp = _UP_owned->GetCharacterMovement();

		FVector Dir = (destPos - _UP_owned->GetActorLocation()).GetSafeNormal();
		movementComp->AddInputVector(Dir);
		// Rot 

		FRotator targetRot = UKismetMathLibrary::FindLookAtRotation(_UP_owned->GetActorLocation(), destPos);
		
		targetRot.Pitch = 0.f;
		targetRot.Roll = 0.f;

		_smoothRot = FMath::RInterpTo(_smoothRot, targetRot, deltaTime, 10.f);

		_UP_owned->SetActorRotation(_smoothRot);


	}
}

void AUNIT_PlayerCT::LookActorOther(class AUNIT_Character* other)
{
	if (_UP_owned == nullptr)
		return;


	//타겟이 x  or  기존에 잡아둔 타겟이 아님 + 본인이 아닐 시 
	if (other && _UP_owned != other)
	{
		//죽었으면 탐지 x
		if (other->GetUnitStates() == EUnitStates::DEAD)
			return;

		SetMouseCursorWidget(EMouseCursor::Default, _WC_CursorAttack->GetUserWidgetObject());
		_ingameMainUI->GetNamePlate()->SetVisibility(ESlateVisibility::Visible);
		_ingameMainUI->GetNamePlate()->BindHp(other->GetStatComp());
		
	

		if (_currentLookTarget.IsValid())
		{
			_currentLookTarget->SetOutline(false);
			_currentLookTarget.Reset();
		}

		SetPostProcessOutline(EOutline::MONSTER);
		_currentLookTarget = other;
		_currentLookTarget->SetOutline(true);

		//TODO : 아웃라인 활성화 

	}
	else
	{
		SetMouseCursorWidget(EMouseCursor::Default, _WC_CursorNormal->GetUserWidgetObject());
		_ingameMainUI->GetNamePlate()->SetVisibility(ESlateVisibility::Hidden);
		

		if (_currentLookTarget.IsValid())
		{
			_currentLookTarget->SetOutline(false);
			
			if (_UP_owned->GetTargetEnemy().IsValid())
			{
				if (_currentLookTarget.Get() == _UP_owned->GetTargetEnemy().Get())
					return;
			}

			//TODO : 아웃라인 비활성화
			_currentLookTarget.Reset();
			

		}

	}

}

void AUNIT_PlayerCT::LookDropItem(class AACT_DropItem* item)
{

	if (_currentLookItem.IsValid())
	{
		_currentLookItem->SetOutline(false);
		_currentLookItem.Reset();
	}

	if (item)
	{	
		SetPostProcessOutline(EOutline::ITEM);
		_currentLookItem = item;
		_currentLookItem->SetOutline(true);
	}
	else
	{
		_currentLookItem.Reset();
	}
	
}

void AUNIT_PlayerCT::ChaseToEnemy(float deltaTime)
{
	if (_UP_owned->GetTargetEnemy().IsValid() == false)
		return;

	float const dist = FVector::Dist(_UP_owned->GetTargetEnemy().Get()->GetActorLocation(), _UP_owned->GetActorLocation());


	if (dist >= 200.f)
	{
		_destPos = _UP_owned->GetTargetEnemy().Get()->GetActorLocation();
	}
	else
	{
		_bMoving = false;

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Attack Enemy"));

		_UP_owned->AttackEnemy();

		_bAttacking = false;

	}

}



void AUNIT_PlayerCT::PickUpItem(float deltaTime)
{
	float const dist = FVector::Dist(_ACT_DropItem->GetActorLocation(), _UP_owned->GetActorLocation());


	if (dist >= 200.f)
	{
		_destPos = _ACT_DropItem->GetActorLocation();
	}
	else
	{	

		_bMoving = false;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Pick up item"));

		bool flag = _ingameMainUI->GetInventory()->AddItem(_ACT_DropItem->GetDropItem());

		if (flag)
		{
			UE_LOG(LogTemp, Log, TEXT("Pick up Item"));
			_ACT_DropItem->Destroy();
		}
		_bPicking = false;
		_pickupCnt = 1;

	}
}


void AUNIT_PlayerCT::CameraShake(float time)
{
	UCameraShakeBase* cam = PlayerCameraManager->StartCameraShake(_CS_NormalAttack, time);
}

void AUNIT_PlayerCT::SetTargetEmpty()
{
	if (_UP_owned->GetTargetEnemy().IsValid())
	{
		_UP_owned->GetTargetEnemy().Reset();
		_UP_owned->SetUnitStates(EUnitStates::IDLE);

	}
}



void AUNIT_PlayerCT::OnMovePressed()
{
	_bClickMouse = _bClickMouseDown = true;
}

void AUNIT_PlayerCT::OnMoveReleased()
{
	_bClickMouse = _bClickMouseDown = false;
}

void AUNIT_PlayerCT::OpenDeadPanel()
{
	
}


void AUNIT_PlayerCT::MainBarSlotEvent()
{
	int32 slotIndex = 0;

	if (IsInputKeyDown(EKeys::One)) slotIndex = 0;
	else if(IsInputKeyDown(EKeys::Two)) slotIndex = 1;
	else if(IsInputKeyDown(EKeys::Three)) slotIndex = 2;
	else if(IsInputKeyDown(EKeys::Four)) slotIndex = 3;
	else if(IsInputKeyDown(EKeys::Five)) slotIndex = 4;
	else if(IsInputKeyDown(EKeys::Six)) slotIndex = 5;
	else if(IsInputKeyDown(EKeys::Seven)) slotIndex = 6;
	else return;

	//TODO : 슬롯 정보 불러옴 - > 캐릭터 스킬 연동
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::FromInt(slotIndex + 1));

	UWG_MainBar_Slot* slot = _ingameMainUI->GetMainBar()->GetMainBarSlot(slotIndex);

	//스킬 아이디를 불러와야 함.. 
	//그 전에..
	//1.쿨타임 체크 .
	//2.마나는 충분한가

	if (slot)
	{
		int32 curMp = _UP_owned->GetStatComp()->GetMp();

		bool bCanSkill = slot->CanUseSkillEvent(curMp);
		ESlotTypes slotType = slot->GetSlotType();

		if(bCanSkill == false || slotType == ESlotTypes::NONE)
			return;

		slot->StartSkillEvent();
		
	}

}



void AUNIT_PlayerCT::OpenInventory()
{
	_ingameMainUI->OpenInventory();
}

void AUNIT_PlayerCT::OpenSkillPanel()
{
	_ingameMainUI->OpenSkill();
}
