// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAnimInstance.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"

void URogueAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	ActionComponent = GetOwningActor()->FindComponentByClass<URogueActionSystemComponent>();
}

void URogueAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!ActionComponent) return;
	
	//@todo: update to use delegates from action system
	bIsSprinting = ActionComponent->ActiveGameplayTags.HasTag(SharedGameplayTags::StatusEffect_Sprinting);
	bIsStunned = ActionComponent->ActiveGameplayTags.HasTag(SharedGameplayTags::StatusEffect_Stunned);
}
