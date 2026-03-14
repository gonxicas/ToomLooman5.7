// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePickUpHeal.h"

#include "ActionSystem/RogueActionSystemComponent.h"


ARoguePickUpHeal::ARoguePickUpHeal()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetCollisionProfileName("NoCollision");
	MeshComponent->SetupAttachment(RootComponent);
}

void ARoguePickUpHeal::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	const auto ActionSystemComponent =
		OtherActor->GetComponentByClass<URogueActionSystemComponent>();
	ensure(ActionSystemComponent);
	check(false);
	if (ActionSystemComponent == nullptr || false/*ActionSystemComponent->IsMaxHealth()*/) return;

	ActionSystemComponent->ApplyHealthChange(HealAmount);
	Super::OnActorOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
