#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "SlashChatacters.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class AWeapon;

UCLASS()
class SLASHINGTHINGS_API ASlashChatacters : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASlashChatacters();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetOverlappingItem(AItem* Item)
	{
		OverlappingItem = Item;
	}

	FORCEINLINE ECharacterState GetChState() const { return CharacterState; };

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveSides(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	virtual bool CanAttack() override;
	void EKeyPressed();
	virtual void Attack() override;

	virtual void PlayAttackMontage() override;
	void PlayEquipMontage(FName SectionName);

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	virtual void AttackEnd() override;

private:
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	// Montages


	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;
};
