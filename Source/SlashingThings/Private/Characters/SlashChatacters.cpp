
#include "Characters/SlashChatacters.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASlashChatacters::ASlashChatacters()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 250.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ViewCamera->SetupAttachment(SpringArm);

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

void ASlashChatacters::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASlashChatacters::LookUp(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("This message will show on the screen!"));
	AddControllerPitchInput(Value);
}

void ASlashChatacters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashChatacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASlashChatacters::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ASlashChatacters::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASlashChatacters::LookUp);
}


