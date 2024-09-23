
#include "Characters/SlashChatacters.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Items/Item.h"
#include "Items/Weapon/Weapon.h"
#include "Animation/AnimMontage.h"

ASlashChatacters::ASlashChatacters()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 250.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ViewCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("eyebrows");

}

void ASlashChatacters::BeginPlay()
{
	Super::BeginPlay();

}

void ASlashChatacters::MoveForward(float Value)
{
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && (Value != 0.f))
	{
		/*FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);*/
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASlashChatacters::MoveSides(float Value)
{
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && (Value != 0.f))
	{
		/*FVector Sides = GetActorRightVector();
		AddMovementInput(Sides, Value);*/
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
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


void ASlashChatacters::Attack()
{
	if (ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped)
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void ASlashChatacters::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon && !EquippedWeapon) {
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandWeapon;
		EquippedWeapon = OverlappingWeapon;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TFuck!"));

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("This message will show on the screen!"));
		if (ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This message will show on the screen!"));

			PlayEquipMontage(FName("Unequip"));
			CharacterState = ECharacterState::ECS_Unequipped;
		}
		else if (ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_Unequipped && EquippedWeapon)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("This message will show on the screen!"));

			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::ECS_EquippedOneHandWeapon;
		}
	}
}


void ASlashChatacters::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		int32 Selection = FMath::RandRange(0, 2);
		FName SectionName = FName();
		switch (Selection)
		{
		default:
			break;
		case 0:
			SectionName = FName("one");
			break;

		case 1:
			SectionName = FName("two");
			break;

		case 2:
			SectionName = FName("three");
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);

	}
}

void ASlashChatacters::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
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
	PlayerInputComponent->BindAxis(FName("MoveSides"), this, &ASlashChatacters::MoveSides);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ASlashChatacters::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASlashChatacters::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("PickUp"), IE_Pressed, this, &ASlashChatacters::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &ASlashChatacters::Attack);

}


