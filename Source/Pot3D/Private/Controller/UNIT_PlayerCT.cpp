#include "Controller/UNIT_PlayerCT.h"
#include <Components/WidgetComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework//CharacterMovementComponent.h>
#include <Components/SceneCaptureComponent2D.h>
#include <Camera/CameraShake.h>
#include <Components/CanvasPanel.h>
#include <Engine/PostProcessVolume.h>
#include "Sound/SoundCue.h"

#include "Creature/UNIT_Character.h"
#include "Creature/UNIT_Player.h"
#include "Creature/UNIT_Monster.h"

#include "Stat/ACP_StatInfo.h"
#include "Skill/ACP_SkillInfo.h"

#include "Item/ACT_DropItem.h"
#include "World/ACT_InteractableObj.h"
#include "Animation/UNIT_Anim.h"

#include "UI/WG_IngameMain.h"
#include "UI/WG_NamePlate.h"
#include "UI/WG_Inventory.h"
#include "UI/WG_MainBar.h"
#include "UI/WG_Skill.h"
#include "UI/WG_MainBar.h"
#include "UI/WG_MainBar_Slot.h"
#include "UI/WG_Minimap.h"

#include "Item/OBJ_Item.h"
#include "Item/ACT_DropItem.h"

#include "World/ACT_InteractableObj.h"

AUNIT_PlayerCT::AUNIT_PlayerCT()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	_WC_CursorNormal = CreateDefaultSubobject<UWidgetComponent>(TEXT("CURSOR_NORMAL"));
	_WC_CursorAttack = CreateDefaultSubobject<UWidgetComponent>(TEXT("CURSOR_ATTACK"));


	TSubclassOf<UUserWidget> CursorNormal; 
	UtilsLib::GetClass<UUserWidget>(&CursorNormal, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_CursorNormal.WBP_CursorNormal_C'"));
	_WC_CursorNormal->SetWidgetClass(CursorNormal);


	TSubclassOf<UUserWidget> CursorAttack;
	UtilsLib::GetClass<UUserWidget>(&CursorAttack, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_CursorAttack.WBP_CursorAttack_C'"));
	_WC_CursorAttack->SetWidgetClass(CursorAttack);

	UtilsLib::GetClass(&_CS_NormalAttack , TEXT("Blueprint'/Game/BluePrints/Camera/BP_CS_NormalAttack.BP_CS_NormalAttack_C'"));
	UtilsLib::GetClass(&_CS_StrongAttack, TEXT("Blueprint'/Game/BluePrints/Camera/BP_CS_StrongAttack.BP_CS_StrongAttack_C'"));
	UtilsLib::GetClass(&_CS_EarthQuake, TEXT("Blueprint'/Game/BluePrints/Camera/BP_CS_EarthQuake.BP_CS_EarthQuake_C'"));


	UtilsLib::GetClass(&_ingameMainClass, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_InGameMain.WBP_InGameMain_C'"));


	UMaterialInterface* MI_Monster;
	UtilsLib::GetAsset(&MI_Monster , TEXT("MaterialInstanceConstant'/Game/Resources/Materials/InteractiveOutline/MI_InteractiveOutline_Monster.MI_InteractiveOutline_Monster'"));

	UMaterialInterface* MI_Item;
	UtilsLib::GetAsset(&MI_Item, TEXT("MaterialInstanceConstant'/Game/Resources/Materials/InteractiveOutline/MI_InteractiveOutline_Item.MI_InteractiveOutline_Item'"));

	UMaterialInterface* MI_Interactable;
	UtilsLib::GetAsset(&MI_Interactable, TEXT("MaterialInstanceConstant'/Game/Resources/Materials/InteractiveOutline/MI_InteractiveOutline_Interactable.MI_InteractiveOutline_Interactable'"));

	_MI_Outlines.Add(MI_Monster);
	_MI_Outlines.Add(MI_Item);
	_MI_Outlines.Add(MI_Interactable);

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

		_ingameMainUI->SetMinimapData();

		//TEST CODE: 
		//_ingameMainUI->GetMainBar()->TestPreSlot();

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

		if(_bUseSkill)
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
		else if (_bInteractable)
			ExecuteInteractableObj(DeltaTime);

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
	InitializePlayerState();
	auto unitCharacter = Cast<AUNIT_Character>(GetPawn());
}

void AUNIT_PlayerCT::ClickMouseCursor()
{

	_bClickMouse = true;


	if (_UP_owned == nullptr)
		return;

	if (_UP_owned->IsAttacking())
		return;

	if (_bAttacking || _bPicking || _bInteractable)
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


	_bClickMouseDown = _bMoving = _bAttacking = _bPicking = _bInteractable = false;
	_bMoving = true;


	//캐릭터 메시 충돌 체크
	FHitResult characterMeshHit;
	GetHitResultUnderCursor(ECC_GameTraceChannel5, false, characterMeshHit);

	//아이템 오브젝트
	FHitResult itemHit;
	GetHitResultUnderCursor(ECC_GameTraceChannel3, false, itemHit);

	//아이템 오브젝트
	FHitResult interactableHit;
	GetHitResultUnderCursor(ECC_GameTraceChannel6, false, interactableHit);

	auto monster = Cast<AUNIT_Monster>(characterMeshHit.Actor);
	auto dropItem = Cast<AACT_DropItem>(itemHit.Actor);
	auto interactableObj = Cast<AACT_InteractableObj>(interactableHit.Actor);

	if (monster == nullptr && dropItem == nullptr && interactableObj == nullptr)
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
	else if (interactableObj)
	{
		_bInteractable = true;
		_ACT_InteractableObj = interactableObj;
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

void AUNIT_PlayerCT::LookOther(class AUNIT_Character* other)
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

		_currentLookTarget = other;


		//아이템을 보고 있는 것이기 때문에, 아웃라인은 실행 안 함
		if (_currentLookItem.IsValid())
			return;

		SetPostProcessOutline(EOutline::MONSTER);
		_currentLookTarget->SetOutline(true);

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
		if(item->IsEnabledOutline() == false)
			return;
	
		_currentLookItem = item;

		//몬스터를 보고 있는 것이기 때문에, 아웃라인은 실행 안 함
		if (_currentLookTarget.IsValid())
			return;

		SetPostProcessOutline(EOutline::ITEM);
		_currentLookItem->SetOutline(true);
	}
	else
	{
		_currentLookItem.Reset();
	}
	
}

void AUNIT_PlayerCT::LookInteractableObj(class AACT_InteractableObj* obj)
{
	if (_currentLookInteractable.IsValid())
	{
		_currentLookInteractable->SetOutline(false);
		_currentLookInteractable.Reset();
	}

	if (obj)
	{
	
		_currentLookInteractable = obj;

		SetPostProcessOutline(EOutline::INTERACTABLE);
		_currentLookInteractable->SetOutline(true);
	}
	else
	{
		_currentLookInteractable.Reset();
	}

}

void AUNIT_PlayerCT::ChaseToEnemy(float deltaTime)
{
	if (_UP_owned->GetTargetEnemy().IsValid() == false)
		return;

	float const dist = FVector::Dist(_UP_owned->GetTargetEnemy().Get()->GetActorLocation(), _UP_owned->GetActorLocation());


	if (dist >= 150.f)
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

	}
}


void AUNIT_PlayerCT::ExecuteInteractableObj(float deltaTime)
{
	float const dist = FVector::Dist(_ACT_InteractableObj->GetActorLocation(), _UP_owned->GetActorLocation());


	if (dist >= 150.f)
	{
		_destPos = _ACT_InteractableObj->GetActorLocation();
	}
	else
	{

		_bMoving = false;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Execute Interatable Object"));


		_ACT_InteractableObj->ExecuteInteractableMethod();
		_bInteractable = false;

	}
}

void AUNIT_PlayerCT::CameraShake(ECameraShake cameraType,  float time)
{
	UCameraShakeBase* cam = nullptr;

	switch (cameraType)
	{
	case ECameraShake::NORMAL:
		cam = PlayerCameraManager->StartCameraShake(_CS_NormalAttack, time);
		break;
	case ECameraShake::STRONG:
		cam = PlayerCameraManager->StartCameraShake(_CS_StrongAttack, time);
		break;
	case ECameraShake::EARTH_QUAKE:
		cam = PlayerCameraManager->StartCameraShake(_CS_EarthQuake, time);
		break;

	default:
		break;
	}


}

void AUNIT_PlayerCT::SetTargetEmpty()
{
	if(_currentLookTarget.IsValid())
		_currentLookTarget.Reset();

	if (_UP_owned->GetTargetEnemy().IsValid())
	{
		_UP_owned->GetTargetEnemy().Reset();

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

USoundCue* AUNIT_PlayerCT::GetUIBtnSound()
{
	USoundCue* cue;
	UtilsLib::GetAssetDynamic(&cue,  TEXT("SoundCue'/Game/Resources/fantasy_gui_4/sounds/btn_pressed_01_Cue.btn_pressed_01_Cue'"));

	return cue;
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


	if(_UP_owned->IsAttacking())
		return;

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

		int32 skillId = slot->GetSKillId();
		UACP_SKillInfo* skillComp = _UP_owned->GetSkillComp();
	
		//아이디가 유효하지 않거나.. 스킬 습득한 정보가 없을 경우
		if(skillId == -1 || skillComp->IsAcquiredSkill(skillId) == false)
			return;
		//플레이어가 현재 스킬을 사용 중인 경우

		if(skillComp->IsUsingSkill())
			return;

		FName skillName = skillComp->GetSkillNameFromId(skillId);
		
		//아이디 등록
		skillComp->SetUsingSKillId(skillId);
		//슬롯에 전달
		slot->StartSkillEvent();
		//캐릭터에 전달 
		_UP_owned->UseActiveSKill(skillName);
		
		//마나감소
		int32 reduceMana = skillComp->GetAcquireSKill(skillId)->_reduceMana;
		int32 newMp = curMp - reduceMana;
		_UP_owned->GetStatComp()->SetMp(newMp);


		//현재 상태들 초기화
		InitializePlayerState();
		_bUseSkill = true;

	}

}



void AUNIT_PlayerCT::OpenInventory()
{

	UtilsLib::SoundPlay2D(GetWorld(), GetUIBtnSound());
	_ingameMainUI->OpenInventory();
}

void AUNIT_PlayerCT::OpenSkillPanel()
{
	UtilsLib::SoundPlay2D(GetWorld(), GetUIBtnSound());
	_ingameMainUI->OpenSkill();
}
