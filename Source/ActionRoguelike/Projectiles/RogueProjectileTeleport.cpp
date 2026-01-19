// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileTeleport.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARogueProjectileTeleport::ARogueProjectileTeleport()
{
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ARogueProjectileTeleport::StartDelayedTeleport, DestroyDelayTime);
	
}

void ARogueProjectileTeleport::StartDelayedTeleport()
{
	TriggerExplosionEffects();
	
	ProjectileMovementComponent->StopMovementImmediately();
	LoopedAudioComponent->Stop();
	LoopedNiagaraComponent->Deactivate();
	SetActorEnableCollision(false);
	
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ARogueProjectileTeleport::HandleTeleport, TeleportSecondaryDelayTime);
}

void ARogueProjectileTeleport::HandleTeleport()
{
	const auto ActorToTeleport = GetInstigator();
	
	check(ActorToTeleport);
	
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	
	Destroy();
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
									   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	StartDelayedTeleport();
}

