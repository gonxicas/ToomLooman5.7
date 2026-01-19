#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectile.generated.h"

class UNiagaraSystem;
class USoundBase;
class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UAudioComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectile : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					FVector NormalImpulse, const FHitResult& Hit );

	void TriggerExplosionEffects() const;

public:
	ARogueProjectile();
	virtual void PostInitializeComponents() override;
};
