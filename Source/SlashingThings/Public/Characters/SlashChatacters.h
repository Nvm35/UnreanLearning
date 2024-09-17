#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "SlashChatacters.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;

UCLASS()
class SLASHINGTHINGS_API ASlashChatacters : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashChatacters();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetOverlappingItem(AItem* Item) {
		OverlappingItem = Item;
	}

	FORCEINLINE ECharacterState GetChState() const { return CharacterState; };

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveSides(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EKeyPressed();

private:

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

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

};
