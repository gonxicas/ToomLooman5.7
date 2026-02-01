#include "RogueAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


ARogueAIController::ARogueAIController()
{
}

void ARogueAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviourTree);

	const auto TargetActor = FName("TargetActor");

	const auto PlayerPawn =  UGameplayStatics::GetPlayerPawn(this, 0);
	
	check(PlayerPawn);
	
	GetBlackboardComponent()->SetValueAsObject(TargetActor, PlayerPawn);
}

