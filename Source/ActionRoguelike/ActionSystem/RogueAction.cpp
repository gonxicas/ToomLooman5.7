#include "RogueAction.h"

#include "ActionRoguelike.h"
#include "RogueActionSystemComponent.h"
#include "Core/RogueGameplayStatics.h"


void URogueAction::StartAction_Implementation()
{
	bIsRunning = true;
	for (auto Cost : ActivationCost)
	{
		GetOwningComponent()->ApplyAttributeChange(Cost.Key, -Cost.Value, Modifier);
	}
	float WorldTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogGame, Log, "Stopped Action {ActionName} - {WorldTime}", ("ActionName", ActionName.ToString()), ("WorldTime", WorldTime));

	CoolDownUntil = GetWorld()->TimeSeconds + CooldownTime;
	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantTags);
}
URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}

bool URogueAction::CanStart() const
{
	if (bIsRunning) return false;
	
	if (GetCooldownTimeRemaining() > 0)
	{
		UE_LOG(LogGame, Log, TEXT("Cooldown remaining: %f"), GetCooldownTimeRemaining());
		return false;
	}

	const auto ActionComp = GetOwningComponent();
	if (ActionComp->ActiveGameplayTags.HasAny(BlockedTags))
		return false;

	for (TPair Cost : ActivationCost)
	{
		if (!URogueGameplayStatics::CanAffordAttribute(ActionComp, Cost))
		{
			UE_LOGFMT(LogGame, Log, "Not enough {AttributeName}, to activate {ActionName}. "
				"Have {AvailableAttributeCost} and need {RequiredAttributeValue}",
				("AttributeName", Cost.Key.ToString()), 
				("ActionName", ActionName.ToString()),
				("AvailableAttributeCost", GetOwningComponent()->GetAttributeValue(Cost.Key)),
				("RequiredAttributeValue", Cost.Value));
			return false;
		}
	}
	
	return true;
}

float URogueAction::GetCooldownTimeRemaining() const
{
	return FMath::Max(0.f,CoolDownUntil - GetWorld()->TimeSeconds);
}


