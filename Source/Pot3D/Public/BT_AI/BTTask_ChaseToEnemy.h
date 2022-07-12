#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChaseToEnemy.generated.h"

UCLASS()
class POT3D_API UBTTask_ChaseToEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ChaseToEnemy();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	
	TWeakObjectPtr<class AUNIT_Player> _target;

};
