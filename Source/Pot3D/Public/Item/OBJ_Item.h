// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UEnumHeader.h"
#include "OBJ_Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType,  Blueprintable, EditInlineNew, DefaultToInstanced)
class POT3D_API UOBJ_Item : public UObject
{
	GENERATED_BODY()

public:

	UOBJ_Item();

public:
	FText& GetItemName() {return _name;}

public:
	void SetItemInfo(int32 id);
	void SetItemType(EItemTypes type) { _itemType = type; }

public:
	class UStaticMesh* GetPickUpMesh() { return _MESH_Pickup; }
	void  SetPickUpMesh(const FName& meshPath);

private:

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 _id;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemTypes _itemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FText _name;

	UPROPERTY(VisibleAnywhere, Category = "Item", meta = (MultiLine=true))
	FText _description;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	bool _isConsumable;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 _count;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FText _iconPath;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName _meshPath;

private:


	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 _slotIndex;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	bool _equipped;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	bool _stackable;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UTexture2D* _TEX_Img;

	UPROPERTY(EditAnywhere, Category = "Item")
	class UStaticMesh* _MESH_Pickup;
	
};

