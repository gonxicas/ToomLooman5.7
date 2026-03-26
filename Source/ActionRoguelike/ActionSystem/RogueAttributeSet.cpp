#include "RogueAttributeSet.h"

#include "RogueActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URogueHealthAttributeSet::URogueHealthAttributeSet() : Health(FRogueAttribute(100)),
                                                       HealthMax(FRogueAttribute(Health.GetValue()))
{
}

URoguePawnAttributeSet::URoguePawnAttributeSet()
{
	MoveSpeed = FRogueAttribute(550);
	MoveSpeedMultiplier = FRogueAttribute(1);
}

URoguePlayerAttributeSet::URoguePlayerAttributeSet()
{
	Rage = FRogueAttribute(0);
}

URogueMonsterAttributeSet::URogueMonsterAttributeSet()
{
	MoveSpeed = FRogueAttribute(450);
}

void URogueHealthAttributeSet::PostAttributeChanged()
{
	Health.Base = FMath::Clamp(Health.Base, 0.f, HealthMax.GetValue());
}

void URoguePawnAttributeSet::ApplyMoveSpeed()
{
	auto OwningCharacter = Cast<ACharacter>(GetOwningComponent()->GetOwner());
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed.GetValue() * MoveSpeedMultiplier.GetValue();
}

void URoguePawnAttributeSet::PostAttributeChanged()
{
	Super::PostAttributeChanged();
	
	ApplyMoveSpeed();
}

void URoguePawnAttributeSet::InitializeAttribute()
{
	Super::InitializeAttribute();
	
	ApplyMoveSpeed();
}


URogueActionSystemComponent* URogueAttributeSet::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}







