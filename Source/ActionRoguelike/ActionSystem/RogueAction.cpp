#include "RogueAction.h"

void URogueAction::StartAction()
{
	float WorldTime = 0.f;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", WorldTime));
}
