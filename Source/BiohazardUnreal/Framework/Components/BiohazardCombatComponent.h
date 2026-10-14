#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/BiohazardTypes.h"
#include "BiohazardCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAmmoStateChanged, int32, CurrentClip, int32, Reserve, EBiohazardWeaponType, WeaponType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, const FBiohazardWeaponData&, NewWeapon);

UCLASS(ClassGroup = (Biohazard), meta = (BlueprintSpawnableComponent))
class BIOHAZARDUNREAL_API UBiohazardCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiohazardCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Weapons")
	TArray<FBiohazardWeaponData> Weapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|Weapons")
	int32 CurrentWeaponIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Combat")
	void Fire(const FVector& CameraLocation, const FVector& CameraForward, AActor* IgnoredActor);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Combat")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Combat")
	void SwitchWeapon(int32 NewIndex);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Combat")
	void AddAmmo(EBiohazardWeaponType WeaponType, int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Biohazard|Combat")
	const FBiohazardWeaponData& GetActiveWeaponData() const;

	UPROPERTY(BlueprintAssignable, Category = "Biohazard|Events")
	FOnAmmoStateChanged OnAmmoStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Biohazard|Events")
	FOnWeaponChanged OnWeaponChanged;

private:
	float FireCooldown = 0.0f;
};
