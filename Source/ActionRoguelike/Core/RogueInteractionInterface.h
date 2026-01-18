#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RogueInteractionInterface.generated.h"

UINTERFACE()
class URogueInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONROGUELIKE_API IRogueInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
};
