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

	// npc + ���� ���� Ȯ��
	void LookActorOther(class AUNIT_Character* other);
	// ��� ������ Ȯ��
	void LookDropItem(class AACT_DropItem* item);


	//�� ����
	void ChaseToEnemy(float deltaTime);

	//������ �ݱ�
	void PickUpItem(float deltaTime);

	void CameraShake(ECameraShake cameraType, float time);
	//Ÿ���� ����� ���
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

	//���� ���콺�� ���� ���� + npc ����
	TWeakObjectPtr<class AUNIT_Character> _currentLookTarget;

	//���� ���콺�� ���� ��� ������ ����
	TWeakObjectPtr<class AACT_DropItem> _currentLookItem;


	//�÷��̾� ĳ����
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
	
	//�Ⱦ� �̽��� 
	int32 _pickupCnt = 0;

	//CAMERA
	//��Ȳ�� �°� ������ ������ ���� ��
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
