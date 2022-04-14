// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	FText& GetItemName() { return _name; }

public:
	bool SetItemInfo(int32 id, int32 count );

public:
	class UStaticMesh* GetPickUpMesh() { return _MESH_Pickup; }
	void  SetPickUpMesh(const FName& meshPath);

protected:

	virtual void PostInitializeComponents() override;


public:
	void CreateItem(int32 id, int32 count , UGI_GmInst* gmInst);


private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _MESH_Comp; 
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WG_Info;


//ÇÊ¿äÇÑ Á¤º¸¸¸ ¼¼ÆÃÇÏ¸é µÊ 
//¶¥¹Ù´Ú¿¡ ¶³±¼°Å¶ó ¤¾ 

private:
	
	UPROPERTY()
	class UGI_GmInst* _gmInst;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 _id;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FText _name;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName _meshPath;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 _count;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UStaticMesh* _MESH_Pickup;

};
