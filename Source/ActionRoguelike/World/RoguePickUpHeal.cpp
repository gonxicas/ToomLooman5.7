// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePickUpHeal.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Core/RogueGameplayStatics.h"


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
	if (ActionSystemComponent == nullptr || URogueGameplayStatics::IsFullHealth(ActionSystemComponent)) return;

	ActionSystemComponent->ApplyAttributeChange(SharedGameplayTags::Attribute_Health, HealAmount, Base);
	Super::OnActorOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
