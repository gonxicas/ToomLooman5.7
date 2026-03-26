#include "URogueBTTask_Heal.h"
#include "AIController.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"

class URogueActionSystemComponent;

EBTNodeResult::Type UURogueBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const ActionSystem = OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass<URogueActionSystemComponent>();;
	check(ActionSystem);

	if (!ensure(ActionSystem)) return EBTNodeResult::Failed;

	ActionSystem->ApplyAttributeChange(SharedGameplayTags::Attribute_Health, HealingAmount, Base);
	return EBTNodeResult::Succeeded;
}
