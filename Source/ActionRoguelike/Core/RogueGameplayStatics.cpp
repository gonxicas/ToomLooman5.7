#include "RogueGameplayStatics.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RogueAttributeSet.h"

bool URogueGameplayStatics::IsFullHealth(URogueActionSystemComponent* ActionComp)
{
	auto Health = ActionComp->GetAttribute(SharedGameplayTags::Attribute_Health);
	auto HealthMax = ActionComp->GetAttribute(SharedGameplayTags::Attribute_HealthMax);
		
	return FMath::IsNearlyEqual(Health->GetValue(), HealthMax->GetValue());
}

float URogueGameplayStatics::GetHealthPercent(URogueActionSystemComponent* ActionComp)
{
	auto Health = ActionComp->GetAttribute(SharedGameplayTags::Attribute_Health);
	auto HealthMax = ActionComp->GetAttribute(SharedGameplayTags::Attribute_HealthMax);
		
	return Health->GetValue() / HealthMax->GetValue();
}

bool URogueGameplayStatics::CanAffordAttribute(const URogueActionSystemComponent* ActionComp, const FGameplayTag InAttribute, const float AttributeCost)
{
	auto Attribute = ActionComp->GetAttribute(InAttribute);
	return Attribute->GetValue() >= AttributeCost;
}

bool URogueGameplayStatics::CanAffordAttribute(const URogueActionSystemComponent* ActionComp, TTuple<FGameplayTag, float> InAttribute)
{
	auto Attribute = ActionComp->GetAttribute(InAttribute.Key);
	return Attribute->GetValue() >= InAttribute.Value;
}
