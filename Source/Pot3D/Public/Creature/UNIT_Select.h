// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UNIT_Select.generated.h"

UCLASS()
class POT3D_API AUNIT_Select : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUNIT_Select();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* _SPC_Arm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* _CAM_Cam;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	float _targetArmLength = 800.f;

};
