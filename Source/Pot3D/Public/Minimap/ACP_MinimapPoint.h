// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACP_MinimapPoint.generated.h"

class UTexture2D;
class UWG_Minimap;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_MinimapPoint : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_MinimapPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void SetIconTexture(UTexture2D* newTexture) { _iconTexure = newTexture; }
	UTexture2D* GetIconTexture() {return _iconTexure;}
	
	void RemoveFromUI();
	

private:


	UPROPERTY(EditAnywhere, Category = "Minimap", meta = (AllowPrivateAccess = true))
	UTexture2D* _iconTexure;
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWG_Minimap* _miniMapUI; 


		
};
