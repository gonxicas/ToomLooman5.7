#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RogueBTTask_RangedAttack.generated.h"

class ARogueProjectile;

UCLASS()
class ACTIONROGUELIKE_API URogueBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FName MuzzleSocketName;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<ARogueProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxBulletSpread = 5.f;
};
