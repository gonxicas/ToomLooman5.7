#include "RogueActionSystemComponent.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void URogueActionSystemComponent::ApplyHealthChange(const float InValueAmount)
{
	Attributes.Health += InValueAmount;

	UE_LOG(LogTemp, Log, TEXT("New Health: %f"), Attributes.Health)
}

