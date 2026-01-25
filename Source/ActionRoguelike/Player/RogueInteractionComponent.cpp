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

	const auto CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();

	constexpr ECollisionChannel CollisionChannel = COLLISION_INTERACTION;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	AActor* BestActor = nullptr;
	float HighestWeight = 0.f;

	const auto bEnableDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();
	const auto InteractionRadiusSquared = InteractionRadius * InteractionRadius;
	for (const auto& Overlap : Overlaps)
	{
		
		FVector Origin; 
		FVector BoxExtends;
		Overlap.GetActor()->GetActorBounds(true, Origin, BoxExtends);
		
		auto OverlapDirection = (Origin - CameraLocation).GetSafeNormal();

		const auto DistanceToSquared = (Origin - Center).SizeSquared();
		const auto NormalizedDistanceTo = 1.f - DistanceToSquared / (InteractionRadiusSquared);

		const auto DotResult = FVector::DotProduct(OverlapDirection,
		                                           PlayerController->GetControlRotation().Vector());

		const auto NormalizeDotResult = DotResult * 0.5f + 0.5f;

		const auto Weight = NormalizeDotResult * DirectionWeightScale + NormalizedDistanceTo * DistanceToWeightScale;
		if (Weight > HighestWeight)
		{
			BestActor = Overlap.GetActor();
			HighestWeight = Weight;
		}
		if (bEnableDebugDraw)
		{
			DrawDebugBox(GetWorld(), Origin, FVector(50.0f), FColor::Red);
			auto DebugString = FString::Printf(
				TEXT("Weight: %f, Dot: %f, Dist: %f"), Weight, NormalizeDotResult, NormalizedDistanceTo);
			DrawDebugString(GetWorld(), Origin, DebugString, nullptr, FColor::Yellow, false, 0.f, true);
		}
	}
	SelectedActor = BestActor;

	if (!bEnableDebugDraw) return;
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);

	if (!SelectedActor) return;

	DrawDebugBox(GetWorld(), SelectedActor->GetActorLocation(), FVector(100.0f), FColor::Green);
}
