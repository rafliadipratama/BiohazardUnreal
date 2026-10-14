#include "Framework/Components/BiohazardHealthComponent.h"

UBiohazardHealthComponent::UBiohazardHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiohazardHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	UpdateCondition();
}

EEcgCondition UBiohazardHealthComponent::GetEcgCondition() const
{
	if (bIsPoisoned) return EEcgCondition::Poison;
	if (CurrentHealth <= 30.0f) return EEcgCondition::Danger;
	if (CurrentHealth <= 65.0f) return EEcgCondition::Caution;
	return EEcgCondition::Fine;
}

void UBiohazardHealthComponent::ApplyDamage(float DamageAmount)
{
	if (CurrentHealth <= 0.0f) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, DamageAmount);
	UpdateCondition();

	if (CurrentHealth <= 0.0f)
	{
		OnPlayerDied.Broadcast();
	}
}

void UBiohazardHealthComponent::Heal(float HealAmount, bool bCurePoison)
{
	if (bCurePoison)
	{
		bIsPoisoned = false;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, -HealAmount);
	UpdateCondition();
}

void UBiohazardHealthComponent::SetPoisoned(bool bPoison)
{
	bIsPoisoned = bPoison;
	UpdateCondition();
}

void UBiohazardHealthComponent::UpdateCondition()
{
	EEcgCondition NewCondition = GetEcgCondition();
	if (NewCondition != LastCondition)
	{
		LastCondition = NewCondition;
		OnEcgConditionChanged.Broadcast(NewCondition);
	}
}
