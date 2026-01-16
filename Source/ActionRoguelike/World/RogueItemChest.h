#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

class UStaticMeshComponent;
UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor
{
	GENERATED_BODY()


protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float CurrentAnimationPitch = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float AnimationSpeed = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float AnimationTargetPitch = 120.f;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	ARogueItemChest();
};
