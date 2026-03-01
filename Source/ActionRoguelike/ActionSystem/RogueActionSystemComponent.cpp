#include "RogueActionSystemComponent.h"

#include "RogueAction.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	auto NewAction = NewObject<URogueAction>(this, URogueAction::StaticClass());
	
	Actions.Add(NewAction);
}

void URogueActionSystemComponent::StartAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StartAction();
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No action found with name %s"), *InActionName.ToString())
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

float URogueActionSystemComponent::GetHealthPercent() const
{
	return Attributes.Health / Attributes.MaxHealth;
}