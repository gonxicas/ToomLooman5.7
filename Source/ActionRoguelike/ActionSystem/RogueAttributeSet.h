#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAttributeSet.generated.h"

USTRUCT()
struct FRogueAttribute
{
	GENERATED_BODY()
	FRogueAttribute(){}

	explicit FRogueAttribute(const float InBase) :	Base(InBase){}


	UPROPERTY(EditAnywhere)
	float Base = 0.f;
	
	UPROPERTY(Transient)
	float Modifier = 0.f;
	
	float GetValue () const { return Base + Modifier; }
	
};

UCLASS()
class ACTIONROGUELIKE_API URogueAttributeSet : public UObject
{
	GENERATED_BODY()
	
	
};

UCLASS()
class URogueHealthAttributeSet : public URogueAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FRogueAttribute Health;
	
	UPROPERTY(EditAnywhere)
	FRogueAttribute HealthMax;
	
	URogueHealthAttributeSet();
	
	
	
};
