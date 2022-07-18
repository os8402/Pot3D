// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UEnumHeader.h"
#include "ACT_DropItem.generated.h"

class UOBJ_Item;
class UGI_GmInst;

UCLASS()
class POT3D_API AACT_DropItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACT_DropItem();

public:
	
	virtual void Tick( float DeltaSeconds ) override;
	virtual void BeginPlay() override;

	class UStaticMesh* GetPickUpMesh() { return _MESH_Pickup; }
	void  SetPickUpMesh();

	void SetOutline(bool on);

	UOBJ_Item* GetDropItem() {return _dropItem;};


protected:

	virtual void PostInitializeComponents() override;


public:
	void CreateItem(UOBJ_Item* newItem);

private:
	UFUNCTION()
	void OnPlaneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _MESH_Comp; 
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* _BOX_Trigger;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WC_Info;




//ÇÊ¿äÇÑ Á¤º¸¸¸ ¼¼ÆÃÇÏ¸é µÊ 
//¶¥¹Ù´Ú¿¡ ¶³±¼°Å¶ó ¤¾ 

private:
	
	UPROPERTY()
	class UGI_GmInst* _gmInst;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UOBJ_Item* _dropItem;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UStaticMesh* _MESH_Pickup;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	class UWG_DropItemInfo* _WG_DropInfo;

	
	bool _bFlotting = true;
	float _timeDestroy;

	float _upforce = 20000.f;
	float _rotforce = 100000.f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float _pitch = 90.f;
	UPROPERTY(EditAnywhere, Category = Movement)
	float _yaw = 0.f;
	UPROPERTY(EditAnywhere, Category = Movement)
	float _roll = 0.f;

	
};
