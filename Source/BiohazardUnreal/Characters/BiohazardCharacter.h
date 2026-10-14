#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/BiohazardTypes.h"
#include "BiohazardCharacter.generated.h"

class UCameraComponent;
class USpotLightComponent;
class UBiohazardHealthComponent;
class UBiohazardInventoryComponent;
class UBiohazardCombatComponent;

UCLASS()
class BIOHAZARDUNREAL_API ABiohazardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABiohazardCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Subobject Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	USpotLightComponent* FlashlightComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|Components")
	UBiohazardHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|Components")
	UBiohazardInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|Components")
	UBiohazardCombatComponent* CombatComponent;

	// Flashlight State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Flashlight")
	float FlashlightBattery = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Flashlight")
	bool bFlashlightActive = true;

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Flashlight")
	void ToggleFlashlight();

	// Actions
	UFUNCTION(BlueprintCallable, Category = "Biohazard|Actions")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Actions")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Actions")
	void Heal();

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Actions")
	void Interact();
};
