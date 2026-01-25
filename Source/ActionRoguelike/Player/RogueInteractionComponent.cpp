#include "RogueInteractionComponent.h"
#include "RogueGameTypes.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"

TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(TEXT("game.interaction.DebugDraw"), false,
                                                       TEXT(
	                                                       "Enables interaction component debug rendering. (0 = off, 1 = enabled)"),
                                                       ECVF_Cheat);

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::Interact()
{
	/*const auto InteractInterface = Cast<IRogueInteractionInterface>(SelectedActor);
	
	
	if (!InteractInterface) return;
	
	InteractInterface->Execute_Interact(this);*/
	if (!SelectedActor) return;
	IRogueInteractionInterface::Execute_Interact(SelectedActor);
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto PlayerController = CastChecked<APlayerController>(GetOwner());

	const auto Center = PlayerController->GetPawn()->GetActorLocation();

	constexpr ECollisionChannel CollisionChannel = COLLISION_INTERACTION;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	AActor* BestActor = nullptr;
	float HighestDotResult = -1.f;

	auto bEnableDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();

	for (const auto& Overlap : Overlaps)
	{
		auto OverlapLocation = Overlap.GetActor()->GetActorLocation();
		auto OverlapDirection = (OverlapLocation - Center).GetSafeNormal();

		const auto DotResult = FVector::DotProduct(OverlapDirection,
												   PlayerController->GetControlRotation().Vector());
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
		if (bEnableDebugDraw)
		{
			DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
			auto DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
			DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::Yellow, false, 0.f, true);
		}
	}

	if (!bEnableDebugDraw) return;
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);

	SelectedActor = BestActor;
	if (!SelectedActor) return

	DrawDebugBox(GetWorld(), SelectedActor->GetActorLocation(), FVector(100.0f), FColor::Green);
}
