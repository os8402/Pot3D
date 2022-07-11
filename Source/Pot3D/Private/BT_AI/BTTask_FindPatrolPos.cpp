
#include "BT_AI/BTTask_FindPatrolPos.h"
#include "Controller/UNIT_MonsterCT.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto curPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(curPawn == nullptr)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(navSystem == nullptr)
		return EBTNodeResult::Failed;

	FNavLocation randLocation;

	if (navSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, randLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")) , randLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

		
}
