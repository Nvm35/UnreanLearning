
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

