#include "RogueAction.h"
#include "RogueActionSystemComponent.h"


void URogueAction::StartAction()
{
	float WorldTime = 0.f;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", WorldTime));
}

URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}