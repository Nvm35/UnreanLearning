#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlashChatacters.generated.h"

UCLASS()
class SLASHINGTHINGS_API ASlashChatacters : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashChatacters();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void	MoveForward(float Value);

};
