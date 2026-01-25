#pragma once

#include "CoreMinimal.h"
#include "RoguePickUp.h"
#include "RoguePickUpHeal.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARoguePickUpHeal : public ARoguePickUp
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	float HealAmount = 50.f;

public:
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	ARoguePickUpHeal();
};
