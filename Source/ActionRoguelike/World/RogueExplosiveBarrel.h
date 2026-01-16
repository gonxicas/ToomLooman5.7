#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class URadialForceComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UStaticMeshComponent;
class USoundBase;
class UAudioComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	ARogueExplosiveBarrel();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float DestroyDelayTime = 1.0f;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                        class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void DestroyBarrel();

public:
	virtual void Tick(float DeltaTime) override;
};
