#include "URogueActionEffect.h"

#include "RogueActionSystemComponent.h"

void UURogueActionEffect::StartAction_Implementation()
{
	Super::StartAction_Implementation();
	
	if (Duration > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(DurationHandle, this, &ThisClass::StopAction, Duration);
	}
}

void UURogueActionEffect::StopAction_Implementation()
{
	Super::StopAction_Implementation();
	
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	
	GetOwningComponent()->RemoveAction(this);
}
