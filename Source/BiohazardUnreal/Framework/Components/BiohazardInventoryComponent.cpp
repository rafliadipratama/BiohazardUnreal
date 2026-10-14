#include "Framework/Components/BiohazardInventoryComponent.h"

UBiohazardInventoryComponent::UBiohazardInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiohazardInventoryComponent::AddGreenHerb(int32 Amount)
{
	GreenHerbs += Amount;
	OnHerbsChanged.Broadcast(GreenHerbs, RedHerbs, FirstAidSprays);
}

void UBiohazardInventoryComponent::AddRedHerb(int32 Amount)
{
	RedHerbs += Amount;
	OnHerbsChanged.Broadcast(GreenHerbs, RedHerbs, FirstAidSprays);
}

void UBiohazardInventoryComponent::AddFirstAidSpray(int32 Amount)
{
	FirstAidSprays += Amount;
	OnHerbsChanged.Broadcast(GreenHerbs, RedHerbs, FirstAidSprays);
}

bool UBiohazardInventoryComponent::ConsumeHerbOrSpray(bool& bOutCurePoison, float& bOutHealAmount)
{
	// Resident Evil Recipe: Green + Red = 100% Heal + Poison cure
	if (GreenHerbs > 0 && RedHerbs > 0)
	{
		GreenHerbs--;
		RedHerbs--;
		bOutCurePoison = true;
		bOutHealAmount = 100.0f;
		OnHerbsChanged.Broadcast(GreenHerbs, RedHerbs, FirstAidSprays);
		return true;
	}

	if (FirstAidSprays > 0)
	{
		FirstAidSprays--;
		bOutCurePoison = true;
		bOutHealAmount = 100.0f;
		OnHerbsChanged.Broadcast(GreenHerbs, RedHerbs, FirstAidSprays);
		return true;
	}

	if (GreenHerbs > 0)
	{
		GreenHerbs--;
		bOutCurePoison = false;
		bOutHealAmount = 35.0f;
		OnHerbsChanged.Broadcast(GreenHerbs, RedHerbs, FirstAidSprays);
		return true;
	}

	return false;
}

void UBiohazardInventoryComponent::AddKey(EBiohazardKeyType Key)
{
	KeyRing.Add(Key);
	OnKeyAdded.Broadcast(Key);
}

bool UBiohazardInventoryComponent::HasKey(EBiohazardKeyType Key) const
{
	return KeyRing.Contains(Key);
}
