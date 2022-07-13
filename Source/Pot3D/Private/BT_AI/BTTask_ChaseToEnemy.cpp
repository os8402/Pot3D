#include "BT_AI/BTTask_ChaseToEnemy.h"
#include "Controller/UNIT_MonsterCT.h"
#include "Creature/UNIT_Player.h"
#include "Creature/UNIT_Monster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include <GameFramework//CharacterMovementComponent.h>


UBTTask_ChaseToEnemy::UBTTask_ChaseToEnemy()
{
	NodeName = TEXT("ChaseToEnemy");
}

EBTNodeResult::Type UBTTask_ChaseToEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	_target = Cast<AUNIT_Player>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

	
	if(_target == nullptr)
		return EBTNodeResult::Failed;


	UAIBlueprintHelperLibrary::SimpleMoveToLocation(OwnerComp.GetAIOwner() , _target.Get()->GetActorLocation());

	
	return EBTNodeResult::Succeeded;

}

void UBTTask_ChaseToEnemy::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//if(_target == nullptr)
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

