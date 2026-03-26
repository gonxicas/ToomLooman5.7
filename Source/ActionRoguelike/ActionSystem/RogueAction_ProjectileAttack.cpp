#include "RogueAction_ProjectileAttack.h"

#include "NiagaraFunctionLibrary.h"
#include "RogueActionSystemComponent.h"
#include "RogueGameTypes.h"
#include "Core/RogueGameplayStatics.h"

#include "Kismet/GameplayStatics.h"

#include "Player/RoguePlayerCharacter.h"

#include "Projectiles/RogueProjectile.h"

TAutoConsoleVariable<float> CVarProjectileAdjustmentDebugDrawing(TEXT("game.projectile.DebugDraw"), false,
                                                                 TEXT(
	                                                                 "Enables projectile adjustment aim debug rendering. (0 = off, > 0 is duration)"),
                                                                 ECVF_Cheat);

URogueAction_ProjectileAttack::URogueAction_ProjectileAttack()
{
	MuzzleSocketName = "Muzzle_01";MuzzleSocketName = "Muzzle_01";
	
	CooldownTime = 0.5f;
}

void URogueAction_ProjectileAttack::StartAction_Implementation()
{
	Super::StartAction_Implementation();

	const auto ActionComp = GetOwningComponent();
	const auto Character = CastChecked<ACharacter>( ActionComp->GetOwner());
	
	if (HasAnyCost && !URogueGameplayStatics::CanAffordAttribute(ActionComp, CostType, CostAmount))
	{
		StopAction();
		UE_LOG(LogTemp, Warning, TEXT("Not enough %s to perform action %s"), *CostType.ToString(), *GetNameSafe(this))
		return;
	}
	if (HasAnyCost)
	{
		ActionComp->ApplyAttributeChange(CostType, -CostAmount, Base);
	}
	
	Character->PlayAnimMontage(AttackMontage);

	FTimerHandle AttackTimerHandle;

	constexpr auto AttackDelayTime = 0.2f;

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, Character->GetMesh(), MuzzleSocketName,
												 FVector::ZeroVector, FRotator::ZeroRotator,
												 EAttachLocation::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ThisClass::AttackTimerElapsed, AttackDelayTime, false);
	
}

void URogueAction_ProjectileAttack::AttackTimerElapsed()
{
	const auto ActionComp = GetOwningComponent();
	const auto Character = CastChecked<ACharacter>( ActionComp->GetOwner());
	
	const auto SpawnLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Character;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	FVector EyeLocation;
	FRotator EyeRotation;

	Character->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	
	const auto TraceEnd = EyeLocation + EyeRotation.Vector() * 5000.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character);

	FVector AdjustedTargetLocation;
	FHitResult Hit;

	auto World = GetWorld();
	auto const bHasHitAnything = World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd,
																 COLLISION_PROJECTILE, QueryParams);

	AdjustedTargetLocation = bHasHitAnything ? Hit.Location : TraceEnd;

	auto SpawnRotation = (AdjustedTargetLocation - SpawnLocation).Rotation();


	auto NewProjectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	Character->MoveIgnoreActorAdd(NewProjectile);
	
	StopAction();
	
#if !UE_BUILD_SHIPPING
	const auto DebugDrawDuration = CVarProjectileAdjustmentDebugDrawing.GetValueOnGameThread();
	if (DebugDrawDuration <= 0.f) return;
	
	//The hit location or trace end
	DrawDebugBox(World, AdjustedTargetLocation, FVector(20.f), FColor::Green, false, DebugDrawDuration);
	//Adjustment line trace
	DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Green, false, DebugDrawDuration);
	//New projectile path
	DrawDebugLine(World, SpawnLocation, AdjustedTargetLocation, FColor::Yellow, false, DebugDrawDuration);
	//The original path of the projectile
	DrawDebugLine(World, SpawnLocation, SpawnLocation + EyeRotation.Vector() * 5000.f, FColor::Purple, false,
				  DebugDrawDuration);
#endif
	
}