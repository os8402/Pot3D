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
	class UStaticMesh* GetPickUpMesh() { return _MESH_Pickup; }
	void  SetPickUpMesh();

	void SetOutline(bool on);


protected:

	virtual void PostInitializeComponents() override;


public:
	void CreateItem(UOBJ_Item* newItem);

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
};
