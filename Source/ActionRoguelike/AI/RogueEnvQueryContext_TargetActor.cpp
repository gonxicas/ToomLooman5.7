#include "RogueEnvQueryContext_TargetActor.h"

#include "AIController.h"
#include "RogueGameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void URogueEnvQueryContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance,
                                                       FEnvQueryContextData& ContextData) const
{

	const auto QuerierPawn =  Cast<APawn>( QueryInstance.Owner.Get());
	if (!ensure(QuerierPawn)) return;
	
	const auto Controller = Cast<AAIController>(QuerierPawn->GetController());
	check(Controller);
	
	const auto TargetActor = Cast<AActor>( Controller->GetBlackboardComponent()->GetValueAsObject(NAME_TargetActor));
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
	
}
