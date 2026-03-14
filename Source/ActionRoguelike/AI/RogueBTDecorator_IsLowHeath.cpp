#include "RogueBTDecorator_IsLowHeath.h"
#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"

class URogueActionSystemComponent;

bool URogueBTDecorator_IsLowHeath::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                              uint8* NodeMemory) const
{
	
	const auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	const auto ActionSystemComponent = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	if (!ensure(ActionSystemComponent)) return false;
	check(false);
	// return ActionSystemComponent->GetHealthPercent() <= LowHealthFraction;
	return true;
}
