#include "RogueBTTask_RangedAttack.h"

#include "AIController.h"
#include "RogueGameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Projectiles/RogueProjectile.h"

URogueBTTask_RangedAttack::URogueBTTask_RangedAttack()
{
	TargetActorKey.SelectedKeyName = NAME_TargetActor;
}

EBTNodeResult::Type URogueBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn()) ;
	check(Character);

	const auto SpawnLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);

	const auto TargetActor = Cast<AActor>( OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (!IsValid(TargetActor)) return EBTNodeResult::Failed;
	
	const auto Direction = TargetActor->GetActorLocation() - SpawnLocation;

	auto SpawnRotation = Direction.Rotation();
	
	SpawnRotation.Pitch += FMath::RandRange(0.f, MaxBulletSpread);
	SpawnRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Character;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const auto NewProjectile =  GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	
	
	return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}