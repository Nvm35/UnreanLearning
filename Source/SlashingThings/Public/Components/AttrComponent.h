#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttrComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLASHINGTHINGS_API UAttrComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttrComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;


};
