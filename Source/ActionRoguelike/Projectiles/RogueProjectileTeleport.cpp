// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileTeleport.h"

#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARogueProjectileTeleport::ARogueProjectileTeleport()
{
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ARogueProjectileTeleport::Explode, DestroyDelayTime);
	
}

void ARogueProjectileTeleport::Explode()
{
	FTimerHandle TimerHandle;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	ProjectileMovementComponent->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARogueProjectileTeleport::ExplodeElapsed, DestroyDelayTime);
}

void ARogueProjectileTeleport::ExplodeElapsed()
{
	
	GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());
	Destroy();
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
									   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ExplodeTimerHandle.Invalidate();
	Explode();
}

