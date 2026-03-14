#include "RogueAction.h"
#include "RogueActionSystemComponent.h"


void URogueAction::StartAction_Implementation()
{
	bIsRunning = true;
	float WorldTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName.ToString()), ("WorldTime", WorldTime));
	GetOwningComponent()->ActiveGameplayTags.AppendTags(GrantTags);
}
void URogueAction::StopAction_Implementation()
{
	bIsRunning = false;
	float WorldTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", ("ActionName", ActionName.ToString()), ("WorldTime", WorldTime));

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
		UE_LOG(LogTemp, Log, TEXT("Cooldown remaining: %f"), GetCooldownTimeRemaining());
		return false;
	}
	
	return !GetOwningComponent()->ActiveGameplayTags.HasAny(BlockedTags);
}

float URogueAction::GetCooldownTimeRemaining() const
{
	return FMath::Max(0.f,CoolDownUntil - GetWorld()->TimeSeconds);
}


