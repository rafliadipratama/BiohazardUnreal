#include "Framework/Components/BiohazardCombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UBiohazardCombatComponent::UBiohazardCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Default classic Biohazard loadout
	FBiohazardWeaponData Pistol;
	Pistol.WeaponType = EBiohazardWeaponType::Pistol9mm;
	Pistol.WeaponName = TEXT("Samurai Edge 9mm");
	Pistol.CurrentMag = 15;
	Pistol.MaxMagCapacity = 15;
	Pistol.ReserveAmmo = 30;
	Pistol.BaseDamage = 35.0f;
	Pistol.FireRate = 0.30f;
	Pistol.MaxRange = 3500.0f;
	Weapons.Add(Pistol);

	FBiohazardWeaponData Shotgun;
	Shotgun.WeaponType = EBiohazardWeaponType::Shotgun12G;
	Shotgun.WeaponName = TEXT("W-870 Riot Shotgun");
	Shotgun.CurrentMag = 7;
	Shotgun.MaxMagCapacity = 7;
	Shotgun.ReserveAmmo = 14;
	Shotgun.BaseDamage = 135.0f;
	Shotgun.FireRate = 0.85f;
	Shotgun.MaxRange = 1600.0f;
	Weapons.Add(Shotgun);

	FBiohazardWeaponData Magnum;
	Magnum.WeaponType = EBiohazardWeaponType::Magnum44;
	Magnum.WeaponName = TEXT("Lightning Hawk .44 Magnum");
	Magnum.CurrentMag = 6;
	Magnum.MaxMagCapacity = 6;
	Magnum.ReserveAmmo = 6;
	Magnum.BaseDamage = 320.0f;
	Magnum.FireRate = 0.95f;
	Magnum.MaxRange = 5000.0f;
	Weapons.Add(Magnum);

	FBiohazardWeaponData Knife;
	Knife.WeaponType = EBiohazardWeaponType::CombatKnife;
	Knife.WeaponName = TEXT("Survival Combat Knife");
	Knife.CurrentMag = 1;
	Knife.MaxMagCapacity = 1;
	Knife.ReserveAmmo = 999;
	Knife.BaseDamage = 25.0f;
	Knife.FireRate = 0.45f;
	Knife.MaxRange = 180.0f;
	Weapons.Add(Knife);
}

void UBiohazardCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Weapons.IsValidIndex(CurrentWeaponIndex))
	{
		const FBiohazardWeaponData& ActiveWeapon = Weapons[CurrentWeaponIndex];
		OnWeaponChanged.Broadcast(ActiveWeapon);
		OnAmmoStateChanged.Broadcast(ActiveWeapon.CurrentMag, ActiveWeapon.ReserveAmmo, ActiveWeapon.WeaponType);
	}
}

void UBiohazardCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FireCooldown > 0.0f)
	{
		FireCooldown -= DeltaTime;
	}
}

void UBiohazardCombatComponent::Fire(const FVector& CameraLocation, const FVector& CameraForward, AActor* IgnoredActor)
{
	if (FireCooldown > 0.0f || !Weapons.IsValidIndex(CurrentWeaponIndex)) return;

	FBiohazardWeaponData& Weapon = Weapons[CurrentWeaponIndex];

	if (Weapon.WeaponType != EBiohazardWeaponType::CombatKnife && Weapon.CurrentMag <= 0)
	{
		return;
	}

	if (Weapon.WeaponType != EBiohazardWeaponType::CombatKnife)
	{
		Weapon.CurrentMag--;
	}

	FireCooldown = Weapon.FireRate;
	OnAmmoStateChanged.Broadcast(Weapon.CurrentMag, Weapon.ReserveAmmo, Weapon.WeaponType);

	// Raycast Hitscan
	FVector Start = CameraLocation;
	FVector End = Start + (CameraForward * Weapon.MaxRange);

	FHitResult Hit;
	FCollisionQueryParams Params;
	if (IgnoredActor)
	{
		Params.AddIgnoredActor(IgnoredActor);
	}

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			UGameplayStatics::ApplyPointDamage(
				HitActor,
				Weapon.BaseDamage,
				CameraForward,
				Hit,
				nullptr,
				GetOwner(),
				UDamageType::StaticClass()
			);
		}
	}
}

void UBiohazardCombatComponent::Reload()
{
	if (!Weapons.IsValidIndex(CurrentWeaponIndex)) return;
	FBiohazardWeaponData& Weapon = Weapons[CurrentWeaponIndex];

	if (Weapon.WeaponType == EBiohazardWeaponType::CombatKnife) return;

	int32 Needed = Weapon.MaxMagCapacity - Weapon.CurrentMag;
	if (Needed <= 0 || Weapon.ReserveAmmo <= 0) return;

	int32 ToLoad = FMath::Min(Needed, Weapon.ReserveAmmo);
	Weapon.CurrentMag += ToLoad;
	Weapon.ReserveAmmo -= ToLoad;
	FireCooldown = 1.25f;

	OnAmmoStateChanged.Broadcast(Weapon.CurrentMag, Weapon.ReserveAmmo, Weapon.WeaponType);
}

void UBiohazardCombatComponent::SwitchWeapon(int32 NewIndex)
{
	if (Weapons.IsValidIndex(NewIndex) && NewIndex != CurrentWeaponIndex)
	{
		CurrentWeaponIndex = NewIndex;
		FireCooldown = 0.35f;

		const FBiohazardWeaponData& ActiveWeapon = Weapons[CurrentWeaponIndex];
		OnWeaponChanged.Broadcast(ActiveWeapon);
		OnAmmoStateChanged.Broadcast(ActiveWeapon.CurrentMag, ActiveWeapon.ReserveAmmo, ActiveWeapon.WeaponType);
	}
}

void UBiohazardCombatComponent::AddAmmo(EBiohazardWeaponType WeaponType, int32 Amount)
{
	for (FBiohazardWeaponData& Weapon : Weapons)
	{
		if (Weapon.WeaponType == WeaponType)
		{
			Weapon.ReserveAmmo += Amount;
			if (Weapons.IndexOfByKey(Weapon) == CurrentWeaponIndex)
			{
				OnAmmoStateChanged.Broadcast(Weapon.CurrentMag, Weapon.ReserveAmmo, Weapon.WeaponType);
			}
			break;
		}
	}
}

const FBiohazardWeaponData& UBiohazardCombatComponent::GetActiveWeaponData() const
{
	check(Weapons.IsValidIndex(CurrentWeaponIndex));
	return Weapons[CurrentWeaponIndex];
}
