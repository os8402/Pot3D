// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UtilsLib.h"
#include "UNIT_SelectCT.generated.h"

class UWG_Select;

UCLASS()
class POT3D_API AUNIT_SelectCT : public APlayerController
{
	GENERATED_BODY()
	
public:

	AUNIT_SelectCT();

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	
	TSubclassOf<UWG_Select> _selectUIClass;
	UWG_Select* _selectUI;


};
