// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UEnumHeader.h"
#include "UNIT_PlayerCT.generated.h"

/**
 * 
 */
class UOBJ_Item;
class UWG_IngameMain;

UCLASS()
class POT3D_API AUNIT_PlayerCT : public APlayerController
{
	GENERATED_BODY()


public :
	AUNIT_PlayerCT();
	virtual void OnPossess(APawn* aPawn);
	virtual void OnUnPossess();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

public:

	void InitPlayerUnit();
	void ClickMouseCursor();
	void ClickMouseDown();

	void SetMoveDest(const FVector destPos, float deltaTime);

	// npc + 몬스터 정보 확인
	void LookActorOther(class AUNIT_Character* other);
	// 드랍 아이템 확인
	void LookDropItem(class AACT_DropItem* item);


	//적 추적
	void ChaseToEnemy(float deltaTime);

	//아이템 줍기
	void PickUpItem(float deltaTime);

	void CameraShake(ECameraShake cameraType, float time);
	//타켓이 사라질 경우
	void SetTargetEmpty();


	void SetPostProcessOutline(EOutline outline);

	void OnMovePressed();
	void OnMoveReleased();

	void OpenInventory();
	void OpenSkillPanel();
	void OpenDeadPanel();

	void MainBarSlotEvent();


	void InitializePlayerState()
	{
		_bClickMouse = _bMoving = _bAttacking = _bPicking = _bUseSkill = false;
	}

	void SetSkillEnded() {_bUseSkill = false;} 
	
public:
	UWG_IngameMain* GetMainUI() {return _ingameMainUI;}

private:


	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WC_CursorNormal;
	
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WC_CursorAttack;

	//현재 마우스로 보는 몬스터 + npc 정보
	TWeakObjectPtr<class AUNIT_Character> _currentLookTarget;

	//현재 마우스로 보는 드랍 아이템 정보
	TWeakObjectPtr<class AACT_DropItem> _currentLookItem;


	//플레이어 캐릭터
	UPROPERTY(VisibleAnywhere)
	class AUNIT_Player* _UP_owned;

	UPROPERTY(VisibleAnywhere)
	class AACT_DropItem* _ACT_DropItem;

//POST PROCESS
private:

	UPROPERTY()
	class APostProcessVolume* _ppv;

	UPROPERTY(EditAnywhere, Category = "Post Process")
	TArray<UMaterialInterface*> _MI_PostProcess;
	
	UPROPERTY(EditAnywhere, Category = "Post Process")
	TArray<UMaterialInterface*> _MI_Outlines;


private:


	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bClickMouse = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bClickMouseDown = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bMoving = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bAttacking = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bPicking = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bUseSkill = 0;

	FVector _destPos;
	FRotator _smoothRot;
	
	float _destRimit;
	
	//픽업 이슈로 
	int32 _pickupCnt = 0;

	//CAMERA
	//상황에 맞게 적절히 가져다 쓰면 됨
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TSubclassOf<class UMatineeCameraShake> _CS_NormalAttack;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TSubclassOf<class UMatineeCameraShake> _CS_StrongAttack;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TSubclassOf<class UMatineeCameraShake> _CS_EarthQuake;

private:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWG_IngameMain> _ingameMainClass;
	UPROPERTY(VisibleAnywhere)
	UWG_IngameMain* _ingameMainUI;




};
