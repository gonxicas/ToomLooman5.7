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

UCLASS()
class ACTIONROGUELIKE_API URogueAttributeSet : public UObject
{
	GENERATED_BODY()

public:
	URogueActionSystemComponent* GetOwningComponent() const;
	
	virtual void InitializeAttribute(){};

	virtual void PostAttributeChanged(){};
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

	virtual void PostAttributeChanged() override;

	URogueHealthAttributeSet();
};

UCLASS()
class ACTIONROGUELIKE_API URoguePawnAttributeSet : public URogueHealthAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	FRogueAttribute MoveSpeed;

	virtual void PostAttributeChanged() override;
	
	virtual void InitializeAttribute() override;
	
	void ApplyMoveSpeed();
	

	URoguePawnAttributeSet();
};

UCLASS()
class ACTIONROGUELIKE_API URoguePlayerAttributeSet : public URoguePawnAttributeSet
{
	GENERATED_BODY()
};

UCLASS()
class ACTIONROGUELIKE_API URogueMonsterAttributeSet : public URoguePawnAttributeSet
{
	GENERATED_BODY()

public:
	URogueMonsterAttributeSet();
};
