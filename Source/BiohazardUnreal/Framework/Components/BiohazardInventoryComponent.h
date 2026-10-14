#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/BiohazardTypes.h"
#include "BiohazardInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHerbsChanged, int32, Green, int32, Red, int32, FirstAid);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeyAdded, EBiohazardKeyType, Key);

UCLASS(ClassGroup = (Biohazard), meta = (BlueprintSpawnableComponent))
class BIOHAZARDUNREAL_API UBiohazardInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiohazardInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Inventory")
	int32 GreenHerbs = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Inventory")
	int32 RedHerbs = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Inventory")
	int32 FirstAidSprays = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|Keys")
	TSet<EBiohazardKeyType> KeyRing;

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Inventory")
	void AddGreenHerb(int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Inventory")
	void AddRedHerb(int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Inventory")
	void AddFirstAidSpray(int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Inventory")
	bool ConsumeHerbOrSpray(bool& bOutCurePoison, float& bOutHealAmount);

	UFUNCTION(BlueprintCallable, Category = "Biohazard|Keys")
	void AddKey(EBiohazardKeyType Key);

	UFUNCTION(BlueprintPure, Category = "Biohazard|Keys")
	bool HasKey(EBiohazardKeyType Key) const;

	UPROPERTY(BlueprintAssignable, Category = "Biohazard|Events")
	FOnHerbsChanged OnHerbsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Biohazard|Events")
	FOnKeyAdded OnKeyAdded;
};
