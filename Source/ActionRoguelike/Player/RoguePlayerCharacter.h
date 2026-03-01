#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguePlayerCharacter.generated.h"

class URogueActionSystemComponent;
class UNiagaraSystem;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS()
class ACTIONROGUELIKE_API ARoguePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARoguePlayerCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TSubclassOf<class ARogueProjectile> ProjectileMagic;

	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;

	
	UPROPERTY(EditDefaultsOnly, Category = "UltimateAttack")
	TSubclassOf<class ARogueProjectile> ProjectileTeleport;
	
	UPROPERTY(EditDefaultsOnly, Category = "SecondaryAttack")
	TSubclassOf<class ARogueProjectile> ProjectileBlackHole;

	UPROPERTY
	(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_Move;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_Look;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_SecondaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_UltimateAttack;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Inputs_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TObjectPtr<UAnimMontage> DeathMontage;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<URogueActionSystemComponent> ActionSystemComponent;
	
	void StartAction(FName InActionName);
	
	void Move(const FInputActionValue& InValue);

	void Look(const FInputActionInstance& InValue);
	void AttackTimerElapsed(TSubclassOf<ARogueProjectile> ProjectileClass);
	void StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass);

	UFUNCTION()
	void OnHealthChanged(float NewHealth, float OldHealth);
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
