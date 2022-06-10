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

	void MoveToMouseCursor(float deltaTime);

	void SetMoveDest(const FVector destPos, float deltaTime);

	// npc + ���� ���� Ȯ��
	void CheckActorOther(class AUNIT_Character* other);
	// ��� ������ Ȯ��
	void CheckDropItem(class AACT_DropItem* item);


	//�� ����
	void ChaseToEnemy(float deltaTime);


	void CameraShake(float time);
	//Ÿ���� ����� ���
	void SetTargetEmpty();


	void SetPostProcessOutline(EOutline outline);

	void OnMovePressed();
	void OnMoveReleased();

	void OpenInventory();
	void OpenDeadPanel();

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



//POST PROCESS
private:

	UPROPERTY()
	class APostProcessVolume* _ppv;

	UPROPERTY(EditAnywhere, Category = "Post Process")
	TArray<UMaterialInterface*> _MID_Outline;
	
private:
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bClickMouse = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bMoving = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn")
	bool _bAttacking = 0;

	FVector _destPos;
	FRotator _smoothRot; 


	UPROPERTY(VisibleAnywhere, Category="Camera")
	TSubclassOf<class UMatineeCameraShake> _CS_NormalAttack;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UWG_IngameMain> _ingameMainClass;
	UWG_IngameMain* _ingameMainUI;


};
