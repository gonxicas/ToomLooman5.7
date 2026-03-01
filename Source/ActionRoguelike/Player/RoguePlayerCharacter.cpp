#include "RoguePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"



ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));
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

	EnhancedInput->BindAction(Inputs_Sprint, ETriggerEvent::Started, this,
							  &ARoguePlayerCharacter::StartAction, FName("Sprint"));
	EnhancedInput->BindAction(Inputs_Sprint, ETriggerEvent::Completed, this,
							  &ARoguePlayerCharacter::StopAction, FName("Sprint"));
	
	EnhancedInput->BindAction(Inputs_PrimaryAttack, ETriggerEvent::Triggered, this,
	                          &ARoguePlayerCharacter::StartAction, FName("PrimaryAttack"));
	EnhancedInput->BindAction(Inputs_SecondaryAttack, ETriggerEvent::Triggered, this,
							  &ARoguePlayerCharacter::StartAction, FName("SecondaryAttack"));
	EnhancedInput->BindAction(Inputs_UltimateAttack, ETriggerEvent::Triggered, this,
							  &ARoguePlayerCharacter::StartAction, FName("SpecialAttack"));
	EnhancedInput->BindAction(Inputs_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);
}

void ARoguePlayerCharacter::StartAction(FName InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARoguePlayerCharacter::StopAction(FName InActionName)
{
	ActionSystemComponent->StopAction(InActionName);
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
