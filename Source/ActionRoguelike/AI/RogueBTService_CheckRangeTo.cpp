#include "RogueBTService_CheckRangeTo.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

void URogueBTService_CheckRangeTo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp =  OwnerComp.GetBlackboardComponent();
	check(BBComp);

	const auto TargetActor = Cast<AActor>( BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!TargetActor) return;
	
	auto Controller = OwnerComp.GetAIOwner();
	check(Controller);

	auto bHasLOS = Controller->LineOfSightTo(TargetActor);

	const auto OwningPawn = Controller->GetPawn();
	check(OwningPawn);

	const auto DistanceTo = FVector::Dist(TargetActor->GetActorLocation(), OwningPawn->GetActorLocation());

	const bool bWithinRange = DistanceTo <= MaxAttackRange;
	
	BBComp->SetValueAsBool(WithinRangeKey.SelectedKeyName, bWithinRange && bHasLOS);
}
