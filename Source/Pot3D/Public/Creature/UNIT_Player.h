// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UNIT_Character.h"
#include "UNIT_Player.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API AUNIT_Player : public AUNIT_Character
{
	GENERATED_BODY()
public:
	AUNIT_Player();

public:

	virtual void Tick(float DeltaTime) override;

public:

	void SearchActorInfo();
	virtual void AttackCheck() override;

public:

	void GetReward(int32 id);


protected:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* _SPC_Arm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* _CAM_Cam;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	float _targetArmLength = 800.f;


};
