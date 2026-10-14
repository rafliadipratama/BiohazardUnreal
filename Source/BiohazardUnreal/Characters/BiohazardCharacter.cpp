#include "Characters/BiohazardCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Framework/Components/BiohazardHealthComponent.h"
#include "Framework/Components/BiohazardInventoryComponent.h"
#include "Framework/Components/BiohazardCombatComponent.h"
#include "Core/Interfaces/BiohazardInteractableInterface.h"

ABiohazardCharacter::ABiohazardCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// First Person Camera
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Flashlight
	FlashlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("TacticalFlashlight"));
	FlashlightComponent->SetupAttachment(FirstPersonCameraComponent);
	FlashlightComponent->SetRelativeLocation(FVector(20.f, 15.f, -10.f));
	FlashlightComponent->Intensity = 5000.f;
	FlashlightComponent->InnerConeAngle = 18.f;
	FlashlightComponent->OuterConeAngle = 38.f;
	FlashlightComponent->AttenuationRadius = 2500.f;

	// Movement Tuning
	GetCharacterMovement()->MaxWalkSpeed = 380.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1200.0f;

	// Clean Actor Components
	HealthComponent = CreateDefaultSubobject<UBiohazardHealthComponent>(TEXT("HealthComponent"));
	InventoryComponent = CreateDefaultSubobject<UBiohazardInventoryComponent>(TEXT("InventoryComponent"));
	CombatComponent = CreateDefaultSubobject<UBiohazardCombatComponent>(TEXT("CombatComponent"));
}

void ABiohazardCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABiohazardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Flashlight battery lifecycle
	if (bFlashlightActive)
	{
		FlashlightBattery = FMath::Clamp(FlashlightBattery - DeltaTime * 0.75f, 0.0f, 100.0f);
		if (FlashlightBattery <= 0.0f)
		{
			FlashlightComponent->SetVisibility(false);
		}
	}
	else
	{
		FlashlightBattery = FMath::Clamp(FlashlightBattery + DeltaTime * 0.4f, 0.0f, 100.0f);
	}
}

void ABiohazardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABiohazardCharacter::AddMovementInput);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ABiohazardCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ABiohazardCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Flashlight"), IE_Pressed, this, &ABiohazardCharacter::ToggleFlashlight);
	PlayerInputComponent->BindAction(TEXT("Heal"), IE_Pressed, this, &ABiohazardCharacter::Heal);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ABiohazardCharacter::Interact);

	PlayerInputComponent->BindAction<FInputSwitchWeaponDelegate>(TEXT("Weapon1"), IE_Pressed, CombatComponent, &UBiohazardCombatComponent::SwitchWeapon, 0);
	PlayerInputComponent->BindAction<FInputSwitchWeaponDelegate>(TEXT("Weapon2"), IE_Pressed, CombatComponent, &UBiohazardCombatComponent::SwitchWeapon, 1);
	PlayerInputComponent->BindAction<FInputSwitchWeaponDelegate>(TEXT("Weapon3"), IE_Pressed, CombatComponent, &UBiohazardCombatComponent::SwitchWeapon, 2);
	PlayerInputComponent->BindAction<FInputSwitchWeaponDelegate>(TEXT("Weapon4"), IE_Pressed, CombatComponent, &UBiohazardCombatComponent::SwitchWeapon, 3);
}

float ABiohazardCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (HealthComponent)
	{
		HealthComponent->ApplyDamage(ActualDamage);
	}
	return ActualDamage;
}

void ABiohazardCharacter::ToggleFlashlight()
{
	if (FlashlightBattery > 5.0f || !bFlashlightActive)
	{
		bFlashlightActive = !bFlashlightActive;
		FlashlightComponent->SetVisibility(bFlashlightActive);
	}
}

void ABiohazardCharacter::Fire()
{
	if (CombatComponent && FirstPersonCameraComponent)
	{
		CombatComponent->Fire(
			FirstPersonCameraComponent->GetComponentLocation(),
			FirstPersonCameraComponent->GetForwardVector(),
			this
		);
	}
}

void ABiohazardCharacter::Reload()
{
	if (CombatComponent)
	{
		CombatComponent->Reload();
	}
}

void ABiohazardCharacter::Heal()
{
	if (!InventoryComponent || !HealthComponent) return;

	bool bCurePoison = false;
	float HealAmount = 0.0f;
	if (InventoryComponent->ConsumeHerbOrSpray(bCurePoison, HealAmount))
	{
		HealthComponent->Heal(HealAmount, bCurePoison);
	}
}

void ABiohazardCharacter::Interact()
{
	if (!FirstPersonCameraComponent) return;

	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * 220.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (HitActor->GetClass()->ImplementsInterface(UBiohazardInteractableInterface::StaticClass()))
			{
				IBiohazardInteractableInterface::Execute_OnPlayerInteract(HitActor, this);
			}
		}
	}
}
