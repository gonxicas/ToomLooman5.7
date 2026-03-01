#include "RogueAction.h"
#include "RogueActionSystemComponent.h"


void URogueAction::StartAction_Implementation()
{
	bIsRunning = true;
	float WorldTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", WorldTime));
}
void URogueAction::StopAction_Implementation()
{
	bIsRunning = false;
	float WorldTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", WorldTime));

	CoolDownUntil = GetWorld()->TimeSeconds + CooldownTime;
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
	return true;
}

float URogueAction::GetCooldownTimeRemaining() const
{
	return FMath::Max(0.f,CoolDownUntil - GetWorld()->TimeSeconds);
}


