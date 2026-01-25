#include "RoguePickUp.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


ARoguePickUp::ARoguePickUp()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("StaticMeshComp"));
	SphereComponent->SetSphereRadius(128.f);
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName(TEXT("Pickup"));
}

void ARoguePickUp::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARoguePickUp::OnActorOverlap);
}

void ARoguePickUp::HandlePickUp()
{
	UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation(), FRotator::ZeroRotator);
	Destroy();
}

void ARoguePickUp::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandlePickUp();
}

