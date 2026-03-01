#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName = FName("PrimaryAttack");
	
public:
	
	
	void StartAction();

	FName GetActionName() const
	{
		return ActionName;
	}
};
