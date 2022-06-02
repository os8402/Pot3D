// Fill out your copyright notice in the Description page of Project Settings.


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
#include "Item/ACT_DropItem.h"
#include "Animation/UNIT_Anim.h"
#include "UI/WG_IngameMain.h"
#include "UI/WG_NamePlate.h"
#include "Item/OBJ_Item.h"


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
		_MID_Outline.Add(MID_MONSTER.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MID_ITEM(TEXT("MaterialInstanceConstant'/Game/Resources/Materials/InteractiveOutline/MI_InteractiveOutline_Item.MI_InteractiveOutline_Item'"));
	if (MID_ITEM.Succeeded())
		_MID_Outline.Add(MID_ITEM.Object);
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
		_ingameMainUI->BindStat(_UP_owned->GetStatComp());
		//_ingameMainUI->UpdateHp();
	}

	//TODO : Post process

	TArray<AActor*> actors;

	UGameplayStatics::GetAllActorsOfClass(this, APostProcessVolume::StaticClass(), actors);

	if (actors.Num() > 0)
	{
		

		_ppv = Cast<APostProcessVolume>(actors[0]);

		if (_ppv)
		{
			FPostProcessSettings& postProcessSettings = _ppv->Settings;
			FWeightedBlendable weightBlendable;
			weightBlendable.Object = _MID_Outline[0];
			weightBlendable.Weight = 1;

			for (int32 i = 0; i < (int32)EPostProcess::END; i++)
			{
				postProcessSettings.WeightedBlendables.Array.Add(weightBlendable);
			}

		}
	}
	
}

void AUNIT_PlayerCT::SetPostProcessOutline(EOutline outline)
{

	FPostProcessSettings& postProcessSettings = _ppv->Settings;

	FWeightedBlendable weightBlendable;
	weightBlendable.Object = _MID_Outline[(int32)outline];
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

		if (_bClickMouse)
			MoveToMouseCursor(DeltaTime);

		if (_bMoving)
			SetMoveDest(_destPos, DeltaTime);
	
		else if (_bAttacking)
			ChaseToEnemy(DeltaTime);

	}

	
}

void AUNIT_PlayerCT::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Move", IE_Pressed, this, &AUNIT_PlayerCT::OnMovePressed);
	InputComponent->BindAction("Move", IE_Released, this, &AUNIT_PlayerCT::OnMoveReleased);
	
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AUNIT_PlayerCT::OpenInventory);
}

void AUNIT_PlayerCT::InitPlayerUnit()
{
	_bClickMouse = _bMoving = _bAttacking = false;

	auto unitCharacter = Cast<AUNIT_Character>(GetPawn());



}

void AUNIT_PlayerCT::MoveToMouseCursor(float deltaTime)
{
	_bClickMouse = true;
	_bAttacking = false;
	_bMoving = false;
//	_DECAL_CursorToWorld->SetVisibility(false);


	if (_UP_owned == nullptr)
		return;

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit == false)
		return;

	auto hit = Cast<AUNIT_Monster>(Hit.Actor);

	EUnitStates state = _UP_owned->GetUnitStates();

	switch (state)
	{

	case EUnitStates::IDLE:

		//타게팅중이였으면 
		//공격으로 변경

		if (_currentLookTarget.IsValid())
		{
			if (hit && hit == _currentLookTarget.Get())
			{
				_UP_owned->SetTargetEnemy(_currentLookTarget.Get());
				// TODO : 아웃라인 _UP_owned->GetTargetEnemy().Get()->

				_UP_owned->SetUnitStates(EUnitStates::ATTACK);

				
		
			}

		}

		break; 

	case EUnitStates::ATTACK:

		//공격 취소

		bool bTarget = _UP_owned->GetTargetEnemy().IsValid();

		if (bTarget)
		{
			if (hit && hit == _UP_owned->GetTargetEnemy().Get())
			{
				//여전히 같은대상임
				_bAttacking = true;
				return;
			}
			


		}

		//취소 진행
		_UP_owned->SetUnitStates(EUnitStates::IDLE);

	//	_ingameMainUI->GetNamePlate()->SetVisibility(ESlateVisibility::Hidden);

		if (bTarget)
		{
			// TODO : 리스너 전부 해제

			/*_owned->GetEnemyTarget().Get()->GetStatComp()->GetOnUnitDied()
				.Remove(targetHandle);

			_owned->GetEnemyTarget().Get()->GetOutLineMesh()->SetVisibility(false);
			_owned->GetEnemyTarget().Reset();*/

		}

		break;

	
	}

	_UP_owned->GetUnitAnim()->StopAllMontages(.1f);
	
	//여기선 이동..
	_destPos = Hit.ImpactPoint;
	_bMoving = true; 




}

void AUNIT_PlayerCT::SetMoveDest(const FVector destPos, float deltaTime)
{
	if (_UP_owned == nullptr)
		return;

	float const dist = FVector::Dist(destPos, _UP_owned->GetActorLocation());

	if (dist > 100.f)
	{
		UCharacterMovementComponent* movementComp = _UP_owned->GetCharacterMovement();
		float speed = movementComp->MaxWalkSpeed;

		FVector Dir = (destPos - _UP_owned->GetActorLocation()).GetSafeNormal();

		movementComp->AddInputVector(Dir);

		FRotator targetRot = UKismetMathLibrary::FindLookAtRotation(_UP_owned->GetActorLocation(), destPos);
		
		targetRot.Pitch = 0.f;
		targetRot.Roll = 0.f;

		_smoothRot = FMath::RInterpTo(_smoothRot, targetRot, deltaTime, 10.f);

		_UP_owned->SetActorRotation(_smoothRot);

		

	}


}

void AUNIT_PlayerCT::CheckActorOther(class AUNIT_Character* other)
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
			//	_currentLookTarget.Get()-> TODO 아웃라인 해제
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
			//	_currentLookTarget.Get()->
		
			_currentLookTarget.Reset();
			

		}

	}

}

void AUNIT_PlayerCT::CheckDropItem(class AACT_DropItem* item)
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

	if (_UP_owned->IsAttacking())
		return;

	float const dist = FVector::Dist(_UP_owned->GetTargetEnemy().Get()->GetActorLocation(), _UP_owned->GetActorLocation());

	if (dist > 200.f)
	{
		SetMoveDest(_UP_owned->GetTargetEnemy().Get()->GetActorLocation(), deltaTime);
	}
	else
	{
		_UP_owned->AttackEnemy();
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
	_bClickMouse = true;
}

void AUNIT_PlayerCT::OnMoveReleased()
{
	_bClickMouse = false;
}

void AUNIT_PlayerCT::OpenDeadPanel()
{

}

bool AUNIT_PlayerCT::AddItem(UOBJ_Item* newItem)
{
	
	if (newItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add Item Failed"));
		return false;
	}
		

	int32 emptySlot = GetEmptySlot();


	if (emptySlot == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Is Full"));
		return false;

	}

	EItemTypes itemtype = newItem->GetItemType();
	
	if (itemtype == EItemTypes::GOLD || itemtype == EItemTypes::JEWEL)
	{
		// TODO : 재화 처리
	}

	else
	{
		_inventoryData.Add(emptySlot, newItem);
	}



	RefreshInventory();

	return true;
}

void AUNIT_PlayerCT::RemoveItem(int32 slot)
{
	
	_inventoryData.Remove(slot);
	RefreshInventory();
}

//consumable
void AUNIT_PlayerCT::UseItem(int32 slot)
{
	//_inventoryData[slot]->_count -= 1;
	RefreshInventory();
}

void AUNIT_PlayerCT::RefreshInventory()
{
	
}

void AUNIT_PlayerCT::OpenInventory()
{
	_ingameMainUI->OpenInventory();
}

int32 AUNIT_PlayerCT::GetEmptySlot()
{
	int32 emptySlot = -1;

	//빈 슬롯 ㅊㅔ크
	for (int32 i = 0; i < _itemMaxSlot; i++)
	{
		UOBJ_Item* const* isItem = _inventoryData.Find(i);
		
		if (isItem == nullptr)
		{
			return i;
		}
	}

	return emptySlot;
}
