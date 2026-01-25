#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoguePickUp.generated.h"

class USphereComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARoguePickUp : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> PickUpSound;
	


public:
	virtual void PostInitializeComponents() override;
	virtual void HandlePickUp();
	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	ARoguePickUp();
};
