#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/BiohazardTypes.h"
#include "BiohazardHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth, float, DamageAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEcgConditionChanged, EEcgCondition, NewCondition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);

UCLASS(ClassGroup = (Biohazard), meta = (BlueprintSpawnableComponent))
class BIOHAZARDUNREAL_API UBiohazardHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiohazardHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Health")
	float CurrentHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Health")
	bool bIsPoisoned = false;

	UFUNCTION(BlueprintPure, Category = "Biohazard|Health")
	EEcgCondition GetEcgCondition() const;

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Health")
	void ApplyDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Health")
	void Heal(float HealAmount, bool bCurePoison = false);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Health")
	void SetPoisoned(bool bPoison);

	UPROPERTY(BlueprintAssignable, Category = "Biohazard|Events")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Biohazard|Events")
	FOnEcgConditionChanged OnEcgConditionChanged;

	UPROPERTY(BlueprintAssignable, Category = "Biohazard|Events")
	FOnPlayerDied OnPlayerDied;

private:
	void UpdateCondition();
	EEcgCondition LastCondition = EEcgCondition::Fine;
};
