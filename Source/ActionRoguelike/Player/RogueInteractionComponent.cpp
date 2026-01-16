#include "RogueInteractionComponent.h"
#include "Engine/OverlapResult.h"

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

	constexpr ECollisionChannel CollisionChannel = ECC_Visibility;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);

	AActor* BestActor = nullptr;
	float HighestDotResult = -1.f;
	
	for (const auto& Overlap : Overlaps)
	{
		auto OverlapLocation = Overlap.GetActor()->GetActorLocation();
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);

		auto OverlapDirection = (OverlapLocation - Center).GetSafeNormal();


		auto DotResult = FVector::DotProduct(OverlapDirection,
		                                     PlayerController->GetControlRotation().Vector());

		auto DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::Yellow, false, 0.f, true);
		
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
	}
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(100.0f), FColor::Green);
	}
}
