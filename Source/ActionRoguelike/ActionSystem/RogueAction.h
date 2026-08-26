#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

class URogueActionSystemComponent;

UCLASS(Blueprintable, Abstract)
class ACTIONROGUELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTag ActionName;
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	float CooldownTime = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTagContainer GrantTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTagContainer BlockedTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TMap<FGameplayTag, float> ActivationCost;
	

public:
	UFUNCTION(BlueprintCallable)
	URogueActionSystemComponent* GetOwningComponent() const;
	
	bool CanStart() const;


	bool IsRunning() const
	{
		return bIsRunning;
	}
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StartAction();
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StopAction();

	float GetCooldownTimeRemaining() const;
	
	FGameplayTag GetActionName() const
	{
		return ActionName;
	}
	
	virtual bool ImplementsGetWorld() const override
	{
		return true;
	}
	
protected:
	UPROPERTY(Transient)
	float CoolDownUntil = 0.f;
	
	UPROPERTY(Transient)
	bool bIsRunning = false;
};
