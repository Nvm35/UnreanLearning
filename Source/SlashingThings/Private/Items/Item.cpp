#include "Items/Item.h"
#include "SlashingThings/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	int32 AvgInt = Avg<int32>(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("AVG = %d"), AvgInt);

	//UWorld* World = GetWorld();

	//SetActorLocation(FVector(0.f, 0.f, 160.f));
	//SetActorRotation(FRotator(0.f, 45.f, 0.f));
	//FVector Location = GetActorLocation();
	//FVector Forward = GetActorForwardVector();


	//DrawSphere(Location);
	//if (World) {
	//	DrawDebugSphere(World, Location, 32.f, 24, FColor::Emerald, false, 60.f);
	//}
	//DRAW_POINT(Location + Forward * 100.f);
	//DRAW_VECTOR(Location, Location + Forward * 500.f)
}

float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}





// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*float MovementRate = 50.f;
	float RotationRate = 30.f;
	AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
	AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));*/

	RunningTime += DeltaTime;

	//float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

	//AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
	DRAW_SPHERE_SINGLEFRAME(GetActorLocation());
	DRAW_VECTOR_SIGNLEFRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100)
}
