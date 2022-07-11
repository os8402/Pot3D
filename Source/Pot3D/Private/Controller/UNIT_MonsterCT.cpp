#include "Controller/UNIT_MonsterCT.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AUNIT_MonsterCT::AUNIT_MonsterCT()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/Resources/AI/BT_MonsterAI.BT_MonsterAI'"));
	if (BT.Succeeded())
	{
		_BT_MonsterAITree = BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/Resources/AI/BB_MonsterAI.BB_MonsterAI'"));
	if (BD.Succeeded())
	{
		_BB_MonsterAIData = BD.Object;
	}

	
}	

void AUNIT_MonsterCT::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(_BB_MonsterAIData, Blackboard))
	{
		if (RunBehaviorTree(_BT_MonsterAITree))
		{

		}
	}

}

void AUNIT_MonsterCT::OnUnPossess()
{
	Super::OnUnPossess();
}
