// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileTeleport.generated.h"

class UNiagaraSystem;

UCLASS()
class ACTIONROGUELIKE_API ARogueProjectileTeleport : public ARogueProjectile
{
	GENERATED_BODY()


protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	virtual void BeginPlay() override;
	void Explode();
	void ExplodeElapsed();
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                FVector NormalImpulse, const FHitResult& Hit) override;

	FTimerHandle ExplodeTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DestroyDelayTime = 0.2f;
	
	
public:
	ARogueProjectileTeleport();
};
