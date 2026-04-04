#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueCoinTestActor.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueCoinTestActor : public AActor
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable)
	void SpawnCoins(int32 SpawnCount);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneComponent;
	
public:
	ARogueCoinTestActor();
};
