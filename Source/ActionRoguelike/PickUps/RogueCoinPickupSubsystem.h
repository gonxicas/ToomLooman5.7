#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RogueCoinPickupSubsystem.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueCoinPickupSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	void AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts);
	void RemoveCoinPickUp(int32 IndexToRemove);
	
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(RogueCoinPickupSubsystem, STATGROUP_Tickables);
	}

protected:
	TArray<FVector> CoinLocations;
	TArray<int32> CoinAmounts;
};
