#include "RogueCoinPickupSubsystem.h"

#include "ActionRoguelike.h"
#include "EngineUtils.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Core/RogueDeveloperSettings.h"
#include "Player/RoguePlayerCharacter.h"

class ARoguePlayerCharacter;

void URogueCoinPickupSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	WorldISM = NewObject<UInstancedStaticMeshComponent>(&InWorld, NAME_None, RF_Transient);
	WorldISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WorldISM->RegisterComponentWithWorld(&InWorld);

	GetDefault<URogueDeveloperSettings>()->CoinPickupMesh.LoadAsync(
		FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &URogueCoinPickupSubsystem::OnPickupMeshLoadComplete));
}

void URogueCoinPickupSubsystem::OnPickupMeshLoadComplete(const FSoftObjectPath& SoftObjectPath, UObject* LoadedObject)
{
	WorldISM->SetStaticMesh(Cast<UStaticMesh>(LoadedObject));
}

void URogueCoinPickupSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	CoinLocations.Append(NewLocations);
	CoinAmounts.Append(NewAmounts);

	TArray<FTransform> MeshTransforms;
	for (int i = 0; i < NewLocations.Num(); ++i)
	{
		MeshTransforms.Add(FTransform(NewLocations[i] + FVector(0.f, 0.f, 50.f)));
	}

	TArray<FPrimitiveInstanceId> NewMeshIDs = WorldISM->AddInstancesById(MeshTransforms, true, false);
	MeshIDs.Append(NewMeshIDs);
}

void URogueCoinPickupSubsystem::RemoveCoinPickUp(int32 IndexToRemove)
{
	CoinLocations.RemoveAt(IndexToRemove);
	CoinAmounts.RemoveAt(IndexToRemove);

	WorldISM->RemoveInstanceById(MeshIDs[IndexToRemove]);
	MeshIDs.RemoveAt(IndexToRemove);
}

void URogueCoinPickupSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const UWorld* World = GetWorld();

	auto PlayerLocation = FVector::Zero();

	for (const auto PlayerCharacter : TActorRange<ARoguePlayerCharacter>(World))
	{
		PlayerLocation = PlayerCharacter->GetActorLocation();
	}

	TArray<int32> ProcessList;

	for (int i = 0; i < CoinLocations.Num(); ++i)
	{
		const float Dist = FVector::Dist(PlayerLocation, CoinLocations[i]);
		if (constexpr float PickupRadius = 200.f; Dist < PickupRadius)
		{
			ProcessList.Add(i);
		}
	}

	int32 TotalCoinsToGrant = 0;
	for (int i = ProcessList.Num() - 1; i >= 0; --i)
	{
		int32 CoinIndex = ProcessList[i];
		TotalCoinsToGrant += CoinAmounts[CoinIndex];

		RemoveCoinPickUp(CoinIndex);
	}
	//@todo: grant coins to player


	UE_CLOG(TotalCoinsToGrant > 0, LogGame, Log, TEXT("Picked up Coin Amount: %d"), TotalCoinsToGrant);
	for (int i = 0; i < CoinLocations.Num(); ++i)
	{
		DrawDebugPoint(World, CoinLocations[i], 8.f, FColor::White);
	}
}
