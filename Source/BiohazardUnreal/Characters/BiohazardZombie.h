#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/BiohazardTypes.h"
#include "BiohazardZombie.generated.h"

class ABiohazardCharacter;

UCLASS()
class BIOHAZARDUNREAL_API ABiohazardZombie : public ACharacter
{
	GENERATED_BODY()

public:
	ABiohazardZombie();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|AI")
	EZombieType ZombieType = EZombieType::StandardWalker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|AI")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|AI")
	float AttackDamage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|AI")
	float AttackRange = 140.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|AI")
	float DetectionRadius = 1200.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|AI")
	bool bIsAlerted = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|AI")
	bool bIsDead = false;

	UFUNCTION(BlueprintCallable, Category = "Biohazard|AI")
	void PerformAttack(ABiohazardCharacter* TargetPlayer);

private:
	float AttackCooldown = 0.0f;
};
