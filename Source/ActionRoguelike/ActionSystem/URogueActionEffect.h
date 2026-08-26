#pragma once

#include "CoreMinimal.h"
#include "RogueAction.h"
#include "URogueActionEffect.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UURogueActionEffect : public URogueAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float Duration = 0.f;
	
	FTimerHandle DurationHandle;

public:
	virtual void StartAction_Implementation() override;
	virtual void StopAction_Implementation() override;
};
