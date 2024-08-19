
#include "Items/Item.h"
#include "SlashingThings/DebugMacros.h"
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

	//DrawLine(Location, Location + Forward * 100.f);
	DrawSphere(Location);
	//if (World) {
	//	DrawDebugSphere(World, Location, 32.f, 24, FColor::Emerald, false, 60.f);
	//}
	//DRAW_POINT(Location + Forward * 100.f);
	DRAW_VECTOR(Location, Location + Forward * 500.f)
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

