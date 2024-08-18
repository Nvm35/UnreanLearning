
#include "Items/Item.h"
#include "DrawDebugHelpers.h"
#include "SlashingThings/SlashingThings.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FVector Forward = GetActorForwardVector();

	if (World) {
		DrawDebugSphere(World, Location, 32.f, 24, FColor::Emerald, false, 60.f);
	}

	DrawLine(Location, Location + Forward * 100.f);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

