#pragma once

#include "CoreMinimal.h"
#include "BiohazardTypes.generated.h"

UENUM(BlueprintType)
enum class EEcgCondition : uint8
{
	Fine        UMETA(DisplayName = "FINE"),
	Caution     UMETA(DisplayName = "CAUTION"),
	Danger      UMETA(DisplayName = "DANGER"),
	Poison      UMETA(DisplayName = "POISON")
};

UENUM(BlueprintType)
enum class EBiohazardWeaponType : uint8
{
	Pistol9mm   UMETA(DisplayName = "Samurai Edge 9mm"),
	Shotgun12G  UMETA(DisplayName = "W-870 Riot Shotgun"),
	Magnum44    UMETA(DisplayName = "Lightning Hawk .44 Magnum"),
	CombatKnife UMETA(DisplayName = "Survival Combat Knife")
};

UENUM(BlueprintType)
enum class EBiohazardKeyType : uint8
{
	SpadeKey      UMETA(DisplayName = "Spade Key"),
	LabKeycard    UMETA(DisplayName = "Level-3 Lab Keycard"),
	HelipadCrest  UMETA(DisplayName = "Omega Helipad Crest")
};

UENUM(BlueprintType)
enum class EZombieType : uint8
{
	StandardWalker UMETA(DisplayName = "T-Virus Zombie"),
	CrimsonStalker UMETA(DisplayName = "Crimson Stalker"),
	TyrantBoss     UMETA(DisplayName = "Tyrant T-002")
};

USTRUCT(BlueprintType)
struct FBiohazardWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EBiohazardWeaponType WeaponType = EBiohazardWeaponType::Pistol9mm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString WeaponName = TEXT("Samurai Edge 9mm");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 CurrentMag = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MaxMagCapacity = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 ReserveAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BaseDamage = 35.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MaxRange = 4000.0f;
};
