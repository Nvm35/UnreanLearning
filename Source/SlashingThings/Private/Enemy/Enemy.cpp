// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Enemy.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AttrComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "HUD/HealthBarComponent.h"
#include "Items/Weapon/Weapon.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarComponent->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 3000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);

	HandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HandCollision"));
	HandCollision->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));

	HandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Disabled initially
	HandCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	HandCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	HandCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AEnemy::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget);
}

void AEnemy::HideHealthBar()
{
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(false);
	}
}

void AEnemy::ShowHealthBar()
{
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(true);
	}
}

void AEnemy::LoseInterest()
{
	CombatTarget = nullptr;
	HideHealthBar();
}

void AEnemy::StartPatrolling()
{
	EnemyState = EEnemyState::EES_Patrolling;
	GetCharacterMovement()->MaxWalkSpeed = PatrollingSpeed;
	MoveToTarget(PatrolTarget);
}

void AEnemy::ChaseTarget()
{
	EnemyState = EEnemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;
	MoveToTarget(CombatTarget);
}

bool AEnemy::IsOutsideCombatRadius()
{
	return !InTargetRange(CombatTarget, CombatRadius);
}

bool AEnemy::IsOutsideAttackRadius()
{
	return !InTargetRange(CombatTarget, AttackRadius);
}

void AEnemy::StartAttackTimer()
{
	EnemyState = EEnemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(AttackMin, AttackMax);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	HealthBarComponent->SetVisibility(false);

	EnemyController = Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
	}

	HandCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHandOverlap);
}

void AEnemy::OnHandOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                           const FHitResult& SweepResult)
{
	// Check if the overlapping actor is the player (or another target)
	if (OtherActor && OtherActor->ActorHasTag(FName("Player")))
	{
		// Apply damage to the player
		//	UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, GetController(), this, UDamageType::StaticClass());
	}
}

void AEnemy::Die()
{
	EnemyState = EEnemyState::EES_Dead;
	PlayDeathMontage();
	HideHealthBar();
	DisableCapsule();
	SetLifeSpan(3.f);
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= Radius;
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(60.f);

	EnemyController->MoveTo(MoveRequest);
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	const bool bShouldChaseTarget =
		EnemyState != EEnemyState::EES_Dead &&
		EnemyState != EEnemyState::EES_Chasing &&
		EnemyState != EEnemyState::EES_Attacking &&
		SeenPawn->ActorHasTag(FName("SlashCharacter"));
	if (EnemyState == EEnemyState::EES_Chasing) return;

	if (bShouldChaseTarget)
	{
		CombatTarget = SeenPawn;
		GetWorldTimerManager().ClearTimer(PatrolTImer);
		ChaseTarget();
	}
}

AActor* AEnemy::ChoosePatrolTarget()
{
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target != PatrolTarget) { ValidTargets.AddUnique(Target); }
	}
	const int32 NumPatrolTargets = ValidTargets.Num();

	if (NumPatrolTargets > 0)
	{
		const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
		return ValidTargets[TargetSelection];
	}

	return nullptr;
}

void AEnemy::Attack()
{
	EnemyState = EEnemyState::EES_Engaged;
	Super::Attack();
	PlayAttackMontage();
}

bool AEnemy::CanAttack()
{
	bool bCanAttack =
		!IsOutsideAttackRadius() &&
		EnemyState != EEnemyState::EES_Attacking &&
		EnemyState != EEnemyState::EES_Engaged &&
		EnemyState != EEnemyState::EES_Dead;
	return bCanAttack;
}


void AEnemy::CheckCombatTarget()
{
	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		if (IsOutsideCombatRadius())
		{
			GetWorldTimerManager().ClearTimer(AttackTimer);
			LoseInterest();
			if (EnemyState != EEnemyState::EES_Engaged) StartPatrolling();
		}
		else if (IsOutsideAttackRadius() && EnemyState != EEnemyState::EES_Chasing)
		{
			GetWorldTimerManager().ClearTimer(AttackTimer);
			if (EnemyState != EEnemyState::EES_Engaged) ChaseTarget();
		}
		else if (CanAttack())
		{
			StartAttackTimer();
		}
	}
}

void AEnemy::Handledamage(float DamageAmount)
{
	Super::Handledamage(DamageAmount);

	if (Attributes && HealthBarComponent)
	{
		HealthBarComponent->SetHealthPercent(Attributes->GetHealthPercent());
	}
}

int32 AEnemy::PlayDeathMontage()
{
	const int32 Selection = Super::PlayDeathMontage();
	TEnumAsByte<EDeathPose> Pose(Selection);
	if (Pose < EDeathPose::EDP_MAX)
	{
		DeathPose = Pose;
	}
	return Selection;
}

void AEnemy::AttackEnd()
{
	EnemyState=EEnemyState::EES_NoState;
	CheckCombatTarget();
	
}

void AEnemy::Tick(float DeltaTime)
{
	if (EnemyState == EEnemyState::EES_Dead) return;

	Super::Tick(DeltaTime);

	CheckCombatTarget();
}


void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	ShowHealthBar();

	if (isAlive())
	{
		DirectionalHitReact(ImpactPoint);
	}
	else Die();

	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                         AActor* DamageCauser)
{
	Handledamage(DamageAmount);
	CombatTarget = EventInstigator->GetPawn();
	ChaseTarget();
	return DamageAmount;
}

void AEnemy::Destroyed()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}
}
