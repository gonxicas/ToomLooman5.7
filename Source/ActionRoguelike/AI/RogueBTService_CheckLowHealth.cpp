#include "RogueBTService_CheckLowHealth.h"
#include "AIController.h"
#include "RogueGameTypes.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

class URogueActionSystemComponent;

URogueBTService_CheckLowHealth::URogueBTService_CheckLowHealth()
{
	IsLowHealthKey.SelectedKeyName = NAME_IsLowHealth;
}

void URogueBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BBComp =  OwnerComp.GetBlackboardComponent();
	check(BBComp);
	
	const auto Character = OwnerComp.GetAIOwner()->GetPawn();
	check(Character);
	
	const auto ActionSystemComponent =
		Character->GetComponentByClass<URogueActionSystemComponent>();
	check(ActionSystemComponent);
	check(false);
	const auto bIsLowHealth = false;//ActionSystemComponent->GetHealthPercent() <= LowHealthFraction;
	BBComp->SetValueAsBool(IsLowHealthKey.SelectedKeyName, bIsLowHealth);
}