#include "RogueCoinPickupSubsystem.h"

#include "ActionRoguelike.h"
#include "EngineUtils.h"
#include "Player/RoguePlayerCharacter.h"

class ARoguePlayerCharacter;

void URogueCoinPickupSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	CoinLocations.Append(NewLocations);
	CoinAmounts.Append(NewAmounts);
}

void URogueCoinPickupSubsystem::RemoveCoinPickUp(int32 IndexToRemove)
{
	CoinLocations.RemoveAt(IndexToRemove);
	CoinAmounts.RemoveAt(IndexToRemove);
}

void URogueCoinPickupSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const UWorld* World = GetWorld();

	auto PlayerLocation = FVector::Zero();
	
	for (const auto PlayerCharacter : TActorRange<ARoguePlayerCharacter> (World))
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
