#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionRadius = 800.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float DistanceToWeightScale = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float DirectionWeightScale = 1.f;

	
	
	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;
	
public:
	
	void Interact() ;
	
	URogueInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
