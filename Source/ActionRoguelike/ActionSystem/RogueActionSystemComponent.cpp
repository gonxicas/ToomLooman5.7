#include "RogueActionSystemComponent.h"

#include "RogueAction.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (const TSubclassOf<URogueAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
}

void URogueActionSystemComponent::StartAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName )
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No action found with name %s"), *InActionName.ToString())
}

void URogueActionSystemComponent::StopAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No action found with name %s"), *InActionName.ToString())
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> NewActionClass)
{
	auto NewAction = NewObject<URogueAction>(this, NewActionClass);

	Actions.Add(NewAction);
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
