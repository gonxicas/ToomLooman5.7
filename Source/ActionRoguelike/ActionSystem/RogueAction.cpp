#include "RogueAction.h"
#include "RogueActionSystemComponent.h"


void URogueAction::StartAction_Implementation()
{
	float WorldTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", WorldTime));
}
void URogueAction::StopAction_Implementation()
{
	float WorldTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", WorldTime));
}
URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}


