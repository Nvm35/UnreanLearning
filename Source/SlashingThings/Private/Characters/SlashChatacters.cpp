
#include "Characters/SlashChatacters.h"

ASlashChatacters::ASlashChatacters()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASlashChatacters::BeginPlay()
{
	Super::BeginPlay();

}

void ASlashChatacters::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
}

void ASlashChatacters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashChatacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASlashChatacters::MoveForward);

}

