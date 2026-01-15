#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class UNiagaraSystem;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS()
class ACTIONROGUELIKE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARogueCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TSubclassOf<class ARogueProjectileMagic> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_Move;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_Look;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_Jump;
	
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InValue);

	void Look(const FInputActionInstance& InValue);
	
	void PrimaryAttack();
	
	void AttackTimerElapsed();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
