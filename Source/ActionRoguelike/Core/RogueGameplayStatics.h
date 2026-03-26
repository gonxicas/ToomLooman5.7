#pragma once

#include "CoreMinimal.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "ActionSystem/RogueAttributeSet.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RogueGameplayStatics.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static bool IsFullHealth(URogueActionSystemComponent* ActionComp)
	{
		auto Health = ActionComp->GetAttribute(SharedGameplayTags::Attribute_Health);
		auto HealthMax = ActionComp->GetAttribute(SharedGameplayTags::Attribute_HealthMax);
		
		return FMath::IsNearlyEqual(Health->GetValue(), HealthMax->GetValue());
	}
	
	static float GetHealthPercent(URogueActionSystemComponent* ActionComp)
	{
		auto Health = ActionComp->GetAttribute(SharedGameplayTags::Attribute_Health);
		auto HealthMax = ActionComp->GetAttribute(SharedGameplayTags::Attribute_HealthMax);
		
		return Health->GetValue() / HealthMax->GetValue();
	}
};
