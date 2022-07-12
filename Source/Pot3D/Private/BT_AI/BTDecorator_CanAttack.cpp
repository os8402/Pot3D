#include "BT_AI/BTDecorator_CanAttack.h"
#include "Controller/UNIT_MonsterCT.h"
#include "Creature/UNIT_Player.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto curPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(curPawn == nullptr)
		return false;

	auto target = Cast<AUNIT_Player>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

	if(target == nullptr)
		return false;

	return bResult && target->GetDistanceTo(curPawn) <= 100.f;

}
