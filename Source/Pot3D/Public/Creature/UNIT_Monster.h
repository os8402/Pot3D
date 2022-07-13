// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UNIT_Character.h"
#include "UtilsLib.h"
#include "UNIT_Monster.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API AUNIT_Monster : public AUNIT_Character
{
	GENERATED_BODY()
	
public:
	AUNIT_Monster();
	virtual void PostInitializeComponents() override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual void DeadUnit() override;
	virtual void VisibleHpBar() override;

private:
	
	UPROPERTY()
	TSubclassOf<class AActor> _ACT_DropItem;

private:

	UPROPERTY(EditAnywhere, Category = "UI")
	float _hpZPos = 250.f;

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector2D _hpDrawSize = { 200.f , 70.f };

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* _WG_HpBar;

	FTimerHandle _hpBarTimer;

};
