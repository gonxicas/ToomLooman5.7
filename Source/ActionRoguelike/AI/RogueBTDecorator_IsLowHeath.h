#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RogueBTDecorator_IsLowHeath.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueBTDecorator_IsLowHeath : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(Editanywhere, Category = "AI")
	FBlackboardKeySelector IsLowHealthKey;
	
	UPROPERTY(Editanywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float LowHealthFraction = 0.3f;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
