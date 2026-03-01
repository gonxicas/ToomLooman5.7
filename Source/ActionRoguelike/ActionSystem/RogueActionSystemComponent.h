#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAction;

USTRUCT(BlueprintType)
struct FRogueAttributeSet
{
	GENERATED_BODY()
	
	FRogueAttributeSet() : MaxHealth(100), Health(MaxHealth)
	{
	}

	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	void StartAction(FName InActionName);
	
	void ApplyHealthChange(float InValueAmount);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	bool IsMaxHealth() const;
	float GetHealthPercent() const;
	virtual void InitializeComponent() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FRogueAttributeSet Attributes;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
public:
	
	URogueActionSystemComponent();
};
