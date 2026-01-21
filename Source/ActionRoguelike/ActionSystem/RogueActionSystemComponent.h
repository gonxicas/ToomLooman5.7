#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

struct FRogueAttributeSet
{
	FRogueAttributeSet() : Health(100.f) {}
	
	float Health;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	void ApplyHealthChange(float InValueAmount);
	
protected:
	FRogueAttributeSet Attributes;
	
public:
	
	
	URogueActionSystemComponent();
};
