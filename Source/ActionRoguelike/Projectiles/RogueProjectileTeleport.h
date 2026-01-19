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
	
	virtual void BeginPlay() override;
	void StartDelayedTeleport();
	void HandleTeleport();
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                FVector NormalImpulse, const FHitResult& Hit) override;

	FTimerHandle ExplodeTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DestroyDelayTime = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportSecondaryDelayTime = 0.2f;
	
	
public:
	ARogueProjectileTeleport();
};
