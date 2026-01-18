#include "RoguePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/RogueProjectileMagic.h"

ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	MuzzleSocketName = "Muzzle_01";
}

void ARoguePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Inputs_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Move);
	EnhancedInput->BindAction(Inputs_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Look);

	EnhancedInput->BindAction(Inputs_PrimaryAttack, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::PrimaryAttack);
	EnhancedInput->BindAction(Inputs_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);
}

void ARoguePlayerCharacter::Move(const FInputActionValue& InValue)
{
	const auto InputValue = InValue.Get<FVector2D>();

	const auto MoveDirection = FVector(InputValue.X, InputValue.Y, 0.0f);

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

void ARoguePlayerCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackMontage);

	FTimerHandle AttackTimerHandle;

	constexpr auto AttackDelayTime = 0.2f;

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
	                                             FVector::ZeroVector, FRotator::ZeroRotator,
	                                             EAttachLocation::SnapToTarget, true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound);

	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ARoguePlayerCharacter::AttackTimerElapsed, AttackDelayTime);
}

void ARoguePlayerCharacter::AttackTimerElapsed()
{
	auto SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);;
	auto SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	MoveIgnoreActorAdd(NewProjectile);
}

void ARoguePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
