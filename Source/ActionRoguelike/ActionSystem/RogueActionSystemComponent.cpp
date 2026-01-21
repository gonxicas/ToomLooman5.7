#include "RogueActionSystemComponent.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void URogueActionSystemComponent::ApplyHealthChange(const float InValueAmount)
{
	const auto OldHealth = Attributes.Health;
	Attributes.Health += InValueAmount;

	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f"), Attributes.Health)
}

