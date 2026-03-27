#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RogueAnimInstance.generated.h"

class URogueActionSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API URogueAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	
	UPROPERTY(Transient, BlueprintReadOnly, Category = "StatusEffect")
	bool bIsSprinting;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<URogueActionSystemComponent> ActionComponent;
};
