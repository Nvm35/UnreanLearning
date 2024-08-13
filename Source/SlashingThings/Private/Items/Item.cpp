
#include "Items/Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Cyan, FString("Checking screen"));
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);

	if (GEngine) {
		FString Message = FString::Printf(TEXT("DeltaTIIIME: %f"), DeltaTime);
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Cyan, Message);
	}
}

