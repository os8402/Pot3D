#include "BT_AI/BTService_SearchTarget.h"
#include "Controller/UNIT_MonsterCT.h"
#include "Creature/UNIT_Player.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory , DeltaSeconds);

	auto curPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(curPawn == nullptr)
		return;

	UWorld* world = curPawn->GetWorld();
	FVector center = curPawn->GetActorLocation();

	float searchRadius = 500.f;

	if(world == nullptr)
		return;

	TArray<FOverlapResult> overlapResults;

	FCollisionQueryParams queryParams(NAME_None, false, curPawn);

	bool bResult =  world->OverlapMultiByChannel(
		overlapResults,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(searchRadius),
		queryParams

		);

	if (bResult)
	{
		for (auto& overlapResult : overlapResults)
		{
			AUNIT_Player* player = Cast<AUNIT_Player>(overlapResult.GetActor());

			if (player)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), player);

				DrawDebugSphere(world, center, searchRadius, 16, FColor::Green, false, 0.2f);

				return;

			}
		}

	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

	DrawDebugSphere(world, center, searchRadius, 16, FColor::Red, false, 0.2f);
}
