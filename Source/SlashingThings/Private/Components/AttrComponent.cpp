
#include "Components/AttrComponent.h"

UAttrComponent::UAttrComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UAttrComponent::BeginPlay()
{
	Super::BeginPlay();



}


void UAttrComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAttrComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

}

float UAttrComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

