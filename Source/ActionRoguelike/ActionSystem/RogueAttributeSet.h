#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAttributeSet.generated.h"

class URogueActionSystemComponent;

USTRUCT()
struct FRogueAttribute
{
	GENERATED_BODY()
	FRogueAttribute()
	{
	}

	explicit FRogueAttribute(const float InBase) : Base(InBase)
	{
	}


	UPROPERTY(EditAnywhere)
	float Base = 0.f;

	UPROPERTY(Transient)
	float Modifier = 0.f;

	float GetValue() const { return Base + Modifier; }
};

UCLASS(EditInlineNew)
class ACTIONROGUELIKE_API URogueAttributeSet : public UObject
{
	GENERATED_BODY()

public:
	URogueActionSystemComponent* GetOwningComponent() const;
	
	virtual void InitializeAttribute(){}

	virtual void PostAttributeChanged(){}
};

UCLASS()
class URogueHealthAttributeSet : public URogueAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Health")
	FRogueAttribute Health;

	UPROPERTY(EditAnywhere, Category = "Health")
	FRogueAttribute HealthMax;

	virtual void PostAttributeChanged() override;

	URogueHealthAttributeSet();
};

UCLASS()
class ACTIONROGUELIKE_API URoguePawnAttributeSet : public URogueHealthAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	FRogueAttribute MoveSpeed;
	
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	FRogueAttribute MoveSpeedMultiplier;
	

	virtual void PostAttributeChanged() override;
	
	virtual void InitializeAttribute() override;
	
	void ApplyMoveSpeed();
	

	URoguePawnAttributeSet();
};

UCLASS()
class ACTIONROGUELIKE_API URoguePlayerAttributeSet : public URoguePawnAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Resources")
	FRogueAttribute Rage;
	
	URoguePlayerAttributeSet();
};

UCLASS()
class ACTIONROGUELIKE_API URogueMonsterAttributeSet : public URoguePawnAttributeSet
{
	GENERATED_BODY()

public:
	URogueMonsterAttributeSet();
};
