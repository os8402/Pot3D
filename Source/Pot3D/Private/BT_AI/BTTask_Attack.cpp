#include "BT_AI/BTTask_Attack.h"
#include "Controller/UNIT_MonsterCT.h"
#include "Creature/UNIT_Character.h"
#include "Creature/UNIT_Player.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick  = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	_BB_Comp = OwnerComp.GetBlackboardComponent();

	auto creature = Cast<AUNIT_Character>(OwnerComp.GetAIOwner()->GetPawn());

	if (creature == nullptr)
		return EBTNodeResult::Failed;


	auto target = Cast<AUNIT_Player>(_BB_Comp->GetValueAsObject(FName(TEXT("Target"))));
	if(target == nullptr)
		return EBTNodeResult::Failed;

	creature->SetTargetEnemy(target);
	creature->AttackEnemy();
	_bIsAttacking = true;
	SetIsAttacking();

	creature->GetOnAttackEnded().AddLambda([this]()
	{
		_bIsAttacking = false;
		SetIsAttacking();

	});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_bIsAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UBTTask_Attack::SetIsAttacking()
{
	_BB_Comp->SetValueAsBool(FName(TEXT("IsAttacking")), _bIsAttacking);
}
