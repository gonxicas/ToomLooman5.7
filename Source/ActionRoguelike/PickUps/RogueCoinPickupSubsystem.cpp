#include "RogueCoinPickupSubsystem.h"

void URogueCoinPickupSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	CoinLocations.Append(NewLocations);
	CoinAmounts.Append(NewAmounts);
}

void URogueCoinPickupSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* World = GetWorld();
	
	for (int i = 0; i < CoinLocations.Num(); ++i)
	{
		DrawDebugPoint(World, CoinLocations[i], 8.f, FColor::White);
	}
}
