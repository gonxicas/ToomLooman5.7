#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RogueBTService_CheckRangeTo.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueBTService_CheckRangeTo : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(Editanywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(Editanywhere, Category = "AI")
	FBlackboardKeySelector WithinRangeKey;
	
	UPROPERTY(Editanywhere, Category = "AI")
	float MaxAttackRange = 500;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	URogueBTService_CheckRangeTo();
	
};
