#include "RogueCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

ARogueCharacter::ARogueCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueCharacter::Move(const FInputActionValue& InValue)
{
	const auto InputValue = InValue.Get<FVector2D>();

	const auto MoveDirection = FVector(InputValue.X, InputValue.Y, 0.0f);
	
	auto ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	
	AddMovementInput(ControlRot.Vector(), InputValue.X);
	
	auto const RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARogueCharacter::Look(const FInputActionInstance& InValue)
{
	const auto InputValue= InValue.GetValue().Get<FVector2D>();
	
	AddControllerPitchInput(-InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Inputs_Move, ETriggerEvent::Triggered, this, &ARogueCharacter::Move);
	EnhancedInput->BindAction(Inputs_Look, ETriggerEvent::Triggered, this, &ARogueCharacter::Look);
}

