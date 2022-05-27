// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UEnumHeader.h"
#include "Item/Inventory.h"
#include "UNIT_PlayerCT.generated.h"

/**
 * 
 */
class UOBJ_Item;

UCLASS()
class POT3D_API AUNIT_PlayerCT : public APlayerController, public IInventory
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

	void OnMovePressed();
	void OnMoveReleased();

	void OpenDeadPanel();

	

private:


	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WC_CursorNormal;
	
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WC_CursorAttack;

	//���� ���콺�� ���� ���� + npc ����
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<class AUNIT_Character> _currentLookTarget;


	//���� ���콺�� ���� ��� ������ ����
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<class AACT_DropItem> _currentLookItem;


	//�÷��̾� ĳ����
	UPROPERTY(VisibleAnywhere)
	class AUNIT_Player* _UP_owned;

	
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
	class UWG_IngameMain* _ingameMainUI;


public:
	virtual TMap<int32, UOBJ_Item*>& GetInventoryData() { return _inventoryData;}
	
public:
	//ITEM

	virtual bool AddItem(UOBJ_Item* newItem);
	virtual void RemoveItem(int32 slot);
	virtual void UseItem(int32 slot);
	virtual void RefreshInventory();
	virtual void OpenInventory();
	virtual int32 GetEmptySlot();

private:
	TMap<int32, UOBJ_Item*> _inventoryData;
	int32 _itemMaxSlot = 20; 

};
