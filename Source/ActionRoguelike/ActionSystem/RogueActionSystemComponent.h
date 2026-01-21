#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FRogueAttributeSet
{
	GENERATED_BODY()
	
	FRogueAttributeSet() : Health(100.f) {}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	void ApplyHealthChange(float InValueAmount);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FRogueAttributeSet Attributes;
	
public:
	
	
	URogueActionSystemComponent();
};
