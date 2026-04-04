#include "RogueCoinTestActor.h"

#include "NavigationSystem.h"
#include "PickUps/RogueCoinPickupSubsystem.h"

ARogueCoinTestActor::ARogueCoinTestActor()
{
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComp"));
	RootComponent = DefaultSceneComponent;
}

void ARogueCoinTestActor::SpawnCoins(int32 SpawnCount)
{
	TArray<FVector>	CoinLocations;
	TArray<int32> CoinAmounts;
	
	auto NavSystem = UNavigationSystemV1::GetNavigationSystem(this);
	FVector ActorLocation = GetActorLocation();
	
	for (int i = 0; i < SpawnCount; i++)
	{
		FNavLocation NavLocation;
		NavSystem->GetRandomPointInNavigableRadius(ActorLocation, 1024.f, NavLocation);
		CoinLocations.Add(NavLocation.Location);
		
		CoinAmounts.Add(10);
	}
	
	auto CoinSystem = GetWorld()->GetSubsystem<URogueCoinPickupSubsystem>();
	
	CoinSystem->AddCoinPickups(CoinLocations, CoinAmounts);
}