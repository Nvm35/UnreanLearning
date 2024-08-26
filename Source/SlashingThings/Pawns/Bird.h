
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Bird.generated.h"

UCLASS()
class SLASHINGTHINGS_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

};
