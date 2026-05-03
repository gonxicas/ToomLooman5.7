#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "RogueDeveloperSettings.generated.h"

class UStaticMesh;

UCLASS(Config = Game, DefaultConfig)
class ACTIONROGUELIKE_API URogueDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditDefaultsOnly, Category = "Pickup")
	TSoftObjectPtr<UStaticMesh> CoinPickupMesh;
	
	virtual FName GetCategoryName() const override
	{
		return FApp::GetProjectName();
	}
};
