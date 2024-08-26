#include "SlashingThings/Pawns/Bird.h"

ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule123"));
	Capsule->SetCapsuleHalfHeight(25.f);
	Capsule->SetCapsuleRadius(14.f);
	RootComponent = Capsule;
}

void ABird::BeginPlay()
{
	Super::BeginPlay();

}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

