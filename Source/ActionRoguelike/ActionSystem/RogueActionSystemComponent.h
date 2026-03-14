#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAttributeSet;
class URogueAction;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	
	void ApplyHealthChange(float InValueAmount);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	bool IsMaxHealth() const;
	float GetHealthPercent() const;
	virtual void InitializeComponent() override;
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
	
	FGameplayTagContainer ActiveGameplayTags;

protected:
	
	UPROPERTY()
	TObjectPtr<URogueAttributeSet> Attributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Attributes", NoClear)
	TSubclassOf<URogueAttributeSet> AttributeSetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
	
public:
	
	URogueActionSystemComponent();
};
