#pragma once

#include "CoreMinimal.h"
#include "RogueAction.h"
#include "RogueAction_ProjectileAttack.generated.h"

class ARogueProjectile;
class UNiagaraSystem;
class USoundBase;
class UAnimMontage;

UCLASS(Abstract)
class ACTIONROGUELIKE_API URogueAction_ProjectileAttack : public URogueAction
{
	GENERATED_BODY()
	
public:
	virtual void StartAction() override;
	
	
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttackc")
	TSubclassOf<ARogueProjectile> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere, Category = "ProjectileAttackc")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttackc")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttackc")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttackc")
	TObjectPtr<USoundBase> CastingSound;
	
	void AttackTimerElapsed();
	
public:
	URogueAction_ProjectileAttack();
	

};
