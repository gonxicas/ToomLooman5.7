#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RogueGameplayStatics.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static bool IsFullHealth(URogueActionSystemComponent* ActionComp);
	
	static float GetHealthPercent(URogueActionSystemComponent* ActionComp);
	
	static bool CanAffordAttribute(const URogueActionSystemComponent* ActionComp, FGameplayTag InAttribute, float AttributeCost);
	static bool CanAffordAttribute(const URogueActionSystemComponent* ActionComp, TTuple<FGameplayTag, float> InAttribute);
};
