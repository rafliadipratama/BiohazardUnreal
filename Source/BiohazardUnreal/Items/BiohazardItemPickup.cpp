#include "Items/BiohazardItemPickup.h"
#include "Characters/BiohazardCharacter.h"
#include "Framework/Components/BiohazardInventoryComponent.h"
#include "Framework/Components/BiohazardCombatComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ABiohazardItemPickup::ABiohazardItemPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(65.0f);
	RootComponent = CollisionSphere;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
}

bool ABiohazardItemPickup::OnPlayerInteract_Implementation(ABiohazardCharacter* InteractingPlayer)
{
	if (!InteractingPlayer) return false;

	switch (PickupType)
	{
	case EBiohazardPickupType::GreenHerb:
		if (InteractingPlayer->InventoryComponent)
		{
			InteractingPlayer->InventoryComponent->AddGreenHerb(Quantity);
		}
		break;

	case EBiohazardPickupType::RedHerb:
		if (InteractingPlayer->InventoryComponent)
		{
			InteractingPlayer->InventoryComponent->AddRedHerb(Quantity);
		}
		break;

	case EBiohazardPickupType::FirstAidSpray:
		if (InteractingPlayer->InventoryComponent)
		{
			InteractingPlayer->InventoryComponent->AddFirstAidSpray(Quantity);
		}
		break;

	case EBiohazardPickupType::Ammo9mm:
		if (InteractingPlayer->CombatComponent)
		{
			InteractingPlayer->CombatComponent->AddAmmo(EBiohazardWeaponType::Pistol9mm, Quantity);
		}
		break;

	case EBiohazardPickupType::AmmoShotgun:
		if (InteractingPlayer->CombatComponent)
		{
			InteractingPlayer->CombatComponent->AddAmmo(EBiohazardWeaponType::Shotgun12G, Quantity);
		}
		break;

	case EBiohazardPickupType::AmmoMagnum:
		if (InteractingPlayer->CombatComponent)
		{
			InteractingPlayer->CombatComponent->AddAmmo(EBiohazardWeaponType::Magnum44, Quantity);
		}
		break;

	case EBiohazardPickupType::KeyItem:
		if (InteractingPlayer->InventoryComponent)
		{
			InteractingPlayer->InventoryComponent->AddKey(KeyItemType);
		}
		break;
	}

	Destroy();
	return true;
}

FText ABiohazardItemPickup::GetInteractionPrompt_Implementation() const
{
	switch (PickupType)
	{
	case EBiohazardPickupType::GreenHerb: return FText::FromString(TEXT("Ambil Green Herb [E]"));
	case EBiohazardPickupType::RedHerb: return FText::FromString(TEXT("Ambil Red Herb [E]"));
	case EBiohazardPickupType::FirstAidSpray: return FText::FromString(TEXT("Ambil First Aid Spray [E]"));
	case EBiohazardPickupType::Ammo9mm: return FText::FromString(TEXT("Ambil Kotak Peluru 9mm [E]"));
	case EBiohazardPickupType::AmmoShotgun: return FText::FromString(TEXT("Ambil Peluru Shotgun [E]"));
	case EBiohazardPickupType::AmmoMagnum: return FText::FromString(TEXT("Ambil Peluru Magnum [E]"));
	case EBiohazardPickupType::KeyItem: return FText::FromString(TEXT("Ambil Kunci Rahasia [E]"));
	default: return FText::FromString(TEXT("Ambil Item [E]"));
	}
}
