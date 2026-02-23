#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "URogueBTTask_Heal.generated.h"
UCLASS()
class ACTIONROGUELIKE_API UURogueBTTask_Heal : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float HealingAmount = 50.f;

};
