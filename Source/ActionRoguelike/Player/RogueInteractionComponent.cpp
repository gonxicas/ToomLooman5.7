#include "RogueInteractionComponent.h"

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto PlayerController = CastChecked<APlayerController>(GetOwner());

	const auto Center = PlayerController->GetPawn()->GetActorLocation();
	
	DrawDebugBox(GetWorld(), Center, FVector(20.0f), FColor::Red);
}

