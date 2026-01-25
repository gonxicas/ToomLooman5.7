#include "RogueActionSystemComponent.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void URogueActionSystemComponent::ApplyHealthChange(const float InValueAmount)
{
	const auto OldHealth = Attributes.Health;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueAmount, 0.0f, Attributes.MaxHealth);

	UE_LOG(LogTemp, Log, TEXT("New Health: %f, Max Health: %f"), Attributes.Health, Attributes.MaxHealth);
	
	if (FMath::IsNearlyEqual(Attributes.Health, OldHealth)) return;

	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
}

bool URogueActionSystemComponent::IsMaxHealth() const
{
	return FMath::IsNearlyEqual(Attributes.Health, Attributes.MaxHealth);
}

