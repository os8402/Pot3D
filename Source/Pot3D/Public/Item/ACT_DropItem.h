// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACT_DropItem.generated.h"

class UOBJ_Item;

UCLASS()
class POT3D_API AACT_DropItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACT_DropItem();

protected:

	virtual void PostInitializeComponents() override;

public:
	void CreateItem(UOBJ_Item* newItem, FVector dropPos);


private:
	UPROPERTY(VisibleAnywhere)
	UOBJ_Item* _item;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _MESH_Comp; 
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WG_Info;

};
