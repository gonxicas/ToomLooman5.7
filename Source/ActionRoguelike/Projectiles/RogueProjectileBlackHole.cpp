#include "RogueProjectileBlackHole.h"

#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueProjectileBlackHole::ARogueProjectileBlackHole()
{
	PrimaryActorTick.bCanEverTick = true;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 1000.f;
	RadialForceComponent->ForceStrength = -150000000.f;
	RadialForceComponent->bAutoActivate = true;
	RadialForceComponent->bIgnoreOwningActor = true;
	SphereComponent->SetCollisionProfileName(TEXT("BlackHole"));
}

void ARogueProjectileBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectileBlackHole::OnActorOverlap);

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARogueProjectileBlackHole::DestroyBlackHole, DestroyDelayTime);
}

void ARogueProjectileBlackHole::DestroyBlackHole()
{
	Destroy();
}

void ARogueProjectileBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueProjectileBlackHole::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}