#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RogueBTService_CheckLowHealth.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueBTService_CheckLowHealth : public UBTService
{
	GENERATED_BODY()
	
	UPROPERTY(Editanywhere, Category = "AI")
	FBlackboardKeySelector IsLowHealthKey;
	
	UPROPERTY(Editanywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float LowHealthFraction = 0.3f;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	URogueBTService_CheckLowHealth();
};
