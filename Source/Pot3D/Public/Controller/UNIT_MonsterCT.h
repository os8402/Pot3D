// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UNIT_MonsterCT.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API AUNIT_MonsterCT : public AAIController
{
	GENERATED_BODY()

public:
	AUNIT_MonsterCT();

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();

private:
	
	FTimerHandle _timerHandle;

	UPROPERTY()
	class UBehaviorTree* _BT_MonsterAITree;

	UPROPERTY()
	class UBlackboardData* _BB_MonsterAIData;
	
};
