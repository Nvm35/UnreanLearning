#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandWeapon UMETA(DisplayName = "EquippedOneHand"),
	ECS_EquippedTwoHandWeapon UMETA(DisplayName = "EquippedTwoHand")
};