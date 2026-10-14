#include "Characters/BiohazardZombie.h"
#include "Characters/BiohazardCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

ABiohazardZombie::ABiohazardZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCharacterMovement()->MaxWalkSpeed = 160.0f;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABiohazardZombie::BeginPlay()
{
	Super::BeginPlay();

	if (ZombieType == EZombieType::CrimsonStalker)
	{
		GetCharacterMovement()->MaxWalkSpeed = 360.0f;
		Health = 140.0f;
		AttackDamage = 35.0f;
	}
	else if (ZombieType == EZombieType::TyrantBoss)
	{
		GetCharacterMovement()->MaxWalkSpeed = 220.0f;
		Health = 650.0f;
		AttackDamage = 50.0f;
		SetActorScale3D(FVector(1.35f));
	}
}

void ABiohazardZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead) return;

	if (AttackCooldown > 0.0f)
	{
		AttackCooldown -= DeltaTime;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return;

	float DistToPlayer = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());

	if (!bIsAlerted && DistToPlayer <= DetectionRadius)
	{
		bIsAlerted = true;
	}

	if (bIsAlerted)
	{
		if (DistToPlayer <= AttackRange && AttackCooldown <= 0.0f)
		{
			if (ABiohazardCharacter* PlayerChar = Cast<ABiohazardCharacter>(PlayerPawn))
			{
				PerformAttack(PlayerChar);
			}
		}
		else
		{
			if (AAIController* AIC = Cast<AAIController>(GetController()))
			{
				AIC->MoveToActor(PlayerPawn, AttackRange * 0.8f);
			}
		}
	}
}

float ABiohazardZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead) return 0.0f;

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= ActualDamage;
	bIsAlerted = true;

	if (Health <= 0.0f)
	{
		bIsDead = true;
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetLifeSpan(15.0f);
	}

	return ActualDamage;
}

void ABiohazardZombie::PerformAttack(ABiohazardCharacter* TargetPlayer)
{
	if (!TargetPlayer || bIsDead) return;

	AttackCooldown = 1.6f;
	UGameplayStatics::ApplyDamage(TargetPlayer, AttackDamage, GetController(), this, UDamageType::StaticClass());
}
