#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "RogueAICharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARogueAICharacter();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URogueActionSystemComponent> ActionSystemComponent;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	FTimerHandle OverlayTimerHandle;
	
};
