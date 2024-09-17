// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashChatacters.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SlashCharacter = Cast<ASlashChatacters>(TryGetPawnOwner());


	if (SlashCharacter)
	{
		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
		/*bIsInAir = SlashCharacter->GetCharacterMovement()->IsFalling();
		bIsAccelerating = SlashCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0;*/
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (SlashCharacterMovement)
	{
		Speed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
		IsFalling = SlashCharacterMovement->IsFalling();
		CharacterState = SlashCharacter->GetChState();
	}

}
