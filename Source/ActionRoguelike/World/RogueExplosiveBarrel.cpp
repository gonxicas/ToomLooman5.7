#include "RogueExplosiveBarrel.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
	RootComponent = MeshComponent;

	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComp"));
	LoopedAudioComponent->SetAutoActivate(false);
	LoopedAudioComponent->SetupAttachment(MeshComponent);

	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComponent->SetAutoActivate(false);
	LoopedNiagaraComponent->SetupAttachment(MeshComponent);
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(MeshComponent);
	RadialForceComponent->Radius = 1000.f;
	RadialForceComponent->ImpulseStrength = 150000.f;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = false;
}

float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	LoopedAudioComponent->Activate();
	LoopedAudioComponent->Play();
	LoopedNiagaraComponent->Activate();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARogueExplosiveBarrel::DestroyBarrel, DestroyDelayTime);
	SetCanBeDamaged(false);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ARogueExplosiveBarrel::DestroyBarrel()
{
	LoopedAudioComponent->Stop();
	LoopedNiagaraComponent->Deactivate();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation()
	                                               , FRotator::ZeroRotator);

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(),
	                                      FRotator::ZeroRotator);
	
	RadialForceComponent->FireImpulse();
	Destroy();
}

void ARogueExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
