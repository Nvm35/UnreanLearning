#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Items/Weapon/Weapon.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Attack()
{
}

void ABaseCharacter::PlayAttackMontage()
{
}

bool ABaseCharacter::CanAttack()
{
	return false;
}

void ABaseCharacter::AttackEnd()
{
}


void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetWeaponCollisionEnable(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		EquippedWeapon->IgnoreActors.Empty();
	}
}
