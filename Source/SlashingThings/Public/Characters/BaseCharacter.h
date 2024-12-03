#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAnimMontage;

UCLASS()
class SLASHINGTHINGS_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnable(ECollisionEnabled::Type CollisionEnabled);

protected:
	virtual void BeginPlay() override;
	virtual void Attack();
	virtual void Die();
	bool isAlive();


	void PlayHitReactMontage(const FName& SectionName);
	void DisableCapsule();
	void DirectionalHitReact(const FVector& ImpactPoint);
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	virtual void Handledamage(float DamageAmount);
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionMontage);
	virtual int32 PlayAttackMontage();
	virtual int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionName);
	virtual int32 PlayDeathMontage();

	virtual bool CanAttack();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	//anims
	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSection;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSection;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;

	UPROPERTY(VisibleAnywhere)
	class UAttrComponent* Attributes;

private:
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;
};
