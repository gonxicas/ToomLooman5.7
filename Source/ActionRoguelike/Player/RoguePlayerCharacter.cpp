#include "RoguePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "RogueGameTypes.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/RogueProjectileMagic.h"

TAutoConsoleVariable<float> CVarProjectileAdjustmentDebugDrawing(TEXT("game.projectile.DebugDraw"), false,
                                               TEXT(
	                                               "Enables projectile adjustment aim debug rendering. (0 = off, > 0 is duration)"),
                                               ECVF_Cheat);

ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));

	MuzzleSocketName = "Muzzle_01";
}


void ARoguePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ARoguePlayerCharacter::OnHealthChanged);
}

void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Inputs_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Move);
	EnhancedInput->BindAction(Inputs_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Look);

	EnhancedInput->BindAction(Inputs_PrimaryAttack, ETriggerEvent::Triggered, this,
	                          &ARoguePlayerCharacter::StartAction, FName("PrimaryAttack"));
	EnhancedInput->BindAction(Inputs_SecondaryAttack, ETriggerEvent::Triggered, this,
	                          &ARoguePlayerCharacter::StartProjectileAttack, ProjectileBlackHole);
	EnhancedInput->BindAction(Inputs_UltimateAttack, ETriggerEvent::Triggered, this,
	                          &ARoguePlayerCharacter::StartProjectileAttack, ProjectileTeleport);
	EnhancedInput->BindAction(Inputs_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);
}

void ARoguePlayerCharacter::StartAction(FName InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARoguePlayerCharacter::Move(const FInputActionValue& InValue)
{
	const auto InputValue = InValue.Get<FVector2D>();

	auto ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;

	AddMovementInput(ControlRot.Vector(), InputValue.X);

	auto const RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARoguePlayerCharacter::Look(const FInputActionInstance& InValue)
{
	const auto InputValue = InValue.GetValue().Get<FVector2D>();

	AddControllerPitchInput(-InputValue.Y);
	AddControllerYawInput(InputValue.X);
}


void ARoguePlayerCharacter::StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass)
{
	PlayAnimMontage(AttackMontage);

	FTimerHandle AttackTimerHandle;

	constexpr auto AttackDelayTime = 0.2f;

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
	                                             FVector::ZeroVector, FRotator::ZeroRotator,
	                                             EAttachLocation::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ARoguePlayerCharacter::AttackTimerElapsed, ProjectileClass);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, Delegate, AttackDelayTime, false);
}

void ARoguePlayerCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if (!FMath::IsNearlyZero(NewHealth)) return;

	DisableInput(nullptr);

	GetMovementComponent()->StopMovementImmediately();

	PlayAnimMontage(DeathMontage);
}

float ARoguePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	auto ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ActionSystemComponent->ApplyHealthChange(-ActualDamage);

	return ActualDamage;
}


void ARoguePlayerCharacter::AttackTimerElapsed(TSubclassOf<ARogueProjectile> ProjectileClass)
{
	const auto SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const auto EyeLocation = CameraComponent->GetComponentLocation();
	const auto EyeRotation = GetControlRotation();
	const auto TraceEnd = EyeLocation + EyeRotation.Vector() * 5000.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector AdjustedTargetLocation;
	FHitResult Hit;

	auto World = GetWorld();
	auto const bHasHitAnything = World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd,
	                                                             COLLISION_PROJECTILE, QueryParams);

	AdjustedTargetLocation = bHasHitAnything ? Hit.Location : TraceEnd;

	auto SpawnRotation = (AdjustedTargetLocation - SpawnLocation).Rotation();


	auto NewProjectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	MoveIgnoreActorAdd(NewProjectile);

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
	DrawDebugLine(World, SpawnLocation, SpawnLocation + GetControlRotation().Vector() * 5000.f, FColor::Purple, false,
	              DebugDrawDuration);
#endif
	
}
