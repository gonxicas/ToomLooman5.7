#include "RogueCoinPickupSubsystem.h"

#include "ActionRoguelike.h"
#include "EngineUtils.h"
#include "Components/AudioComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Core/RogueDeveloperSettings.h"
#include "Player/RoguePlayerCharacter.h"
#include "ProfilingDebugging/CountersTrace.h"

TRACE_DECLARE_INT_COUNTER(CoinInstanceCount, TEXT("Coin in World"));

class ARoguePlayerCharacter;

void URogueCoinPickupSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	auto World = GetWorld();

	WorldISM = NewObject<UInstancedStaticMeshComponent>(World, NAME_None, RF_Transient);
	WorldISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WorldISM->RegisterComponentWithWorld(World);

	TRACE_COUNTER_SET(CoinInstanceCount, 0);
	
	const auto DevSettings = GetDefault<URogueDeveloperSettings>();
	CachedCoinPickupTriggerParamName = DevSettings->CoinPickupTriggerParameter;

	DevSettings->CoinPickupMesh.LoadAsync(
		FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &URogueCoinPickupSubsystem::OnPickupMeshLoadComplete));

	WorldAudioComponent = NewObject<UAudioComponent>(World, NAME_None, RF_Transient);
	WorldAudioComponent->SetAutoActivate(false);
	WorldAudioComponent->RegisterComponentWithWorld(World);
	WorldAudioComponent->bAllowSpatialization = false;
	
	DevSettings->CoinPickupSound.LoadAsync(
		FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &URogueCoinPickupSubsystem::OnPickupSoundLoadComplete));
}

void URogueCoinPickupSubsystem::OnPickupMeshLoadComplete(const FSoftObjectPath& SoftObjectPath, UObject* LoadedObject)
{
	WorldISM->SetStaticMesh(Cast<UStaticMesh>(LoadedObject));
}

void URogueCoinPickupSubsystem::OnPickupSoundLoadComplete(const FSoftObjectPath& SoftObjectPath, UObject* LoadedObject)
{
	WorldAudioComponent->SetSound(Cast<USoundBase>(LoadedObject));
}

void URogueCoinPickupSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::AddCoinPickups);

	CoinLocations.Append(NewLocations);
	CoinAmounts.Append(NewAmounts);

	TArray<FTransform> MeshTransforms;
	for (int i = 0; i < NewLocations.Num(); ++i)
	{
		MeshTransforms.Add(FTransform(NewLocations[i] + FVector(0.f, 0.f, 50.f)));
	}

	TArray<FPrimitiveInstanceId> NewMeshIDs = WorldISM->AddInstancesById(MeshTransforms, true, false);
	MeshIDs.Append(NewMeshIDs);
	
	TRACE_COUNTER_SET(CoinInstanceCount, CoinLocations.Num());
}

void URogueCoinPickupSubsystem::RemoveCoinPickUp(int32 IndexToRemove)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::RemoveCoinPickUp);

	CoinLocations.RemoveAt(IndexToRemove);
	CoinAmounts.RemoveAt(IndexToRemove);

	WorldISM->RemoveInstanceById(MeshIDs[IndexToRemove]);
	MeshIDs.RemoveAt(IndexToRemove);
	TRACE_COUNTER_SET(CoinInstanceCount, CoinLocations.Num());
}

void URogueCoinPickupSubsystem::PlayPickupSound()
{
	if (!WorldAudioComponent->IsPlaying())
	{
		WorldAudioComponent->Play();
	}


	WorldAudioComponent->SetTriggerParameter(CachedCoinPickupTriggerParamName);
}

void URogueCoinPickupSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::Tick);

	const UWorld* World = GetWorld();

	auto PlayerLocation = FVector::Zero();

	for (const auto PlayerCharacter : TActorRange<ARoguePlayerCharacter>(World))
	{
		PlayerLocation = PlayerCharacter->GetActorLocation();
	}

	TArray<int32> ProcessList;

	{
		TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::Tick::DistanceCheck);
		for (int i = 0; i < CoinLocations.Num(); ++i)
		{
			const float Dist = FVector::Dist(PlayerLocation, CoinLocations[i]);
			if (constexpr float PickupRadius = 200.f; Dist < PickupRadius)
			{
				ProcessList.Add(i);
			}
		}
	}


	int32 TotalCoinsToGrant = 0;
	
	{
		TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::Tick::HandlePickUps);
		for (int i = ProcessList.Num() - 1; i >= 0; --i)
		{
			int32 CoinIndex = ProcessList[i];
			TotalCoinsToGrant += CoinAmounts[CoinIndex];

			RemoveCoinPickUp(CoinIndex);
		}
	}
	

	if (TotalCoinsToGrant > 0)
	{
		PlayPickupSound();
	}
	//@todo: grant coins to player

#if 0
	UE_CLOG(TotalCoinsToGrant > 0, LogGame, Log, TEXT("Picked up Coin Amount: %d"), TotalCoinsToGrant);
	for (int i = 0; i < CoinLocations.Num(); ++i)
	{
		DrawDebugPoint(World, CoinLocations[i], 8.f, FColor::White);
	}
#endif
	
}
