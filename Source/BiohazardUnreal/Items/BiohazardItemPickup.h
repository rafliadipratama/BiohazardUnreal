#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/BiohazardInteractableInterface.h"
#include "Core/BiohazardTypes.h"
#include "BiohazardItemPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EBiohazardPickupType : uint8
{
	GreenHerb     UMETA(DisplayName = "Green Herb"),
	RedHerb       UMETA(DisplayName = "Red Herb"),
	FirstAidSpray UMETA(DisplayName = "First Aid Spray"),
	Ammo9mm       UMETA(DisplayName = "9mm Ammo Box"),
	AmmoShotgun   UMETA(DisplayName = "Shotgun Shells"),
	AmmoMagnum    UMETA(DisplayName = ".44 Magnum Rounds"),
	KeyItem       UMETA(DisplayName = "Key Item")
};

UCLASS()
class BIOHAZARDUNREAL_API ABiohazardItemPickup : public AActor, public IBiohazardInteractableInterface
{
	GENERATED_BODY()

public:
	ABiohazardItemPickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Pickup")
	EBiohazardPickupType PickupType = EBiohazardPickupType::GreenHerb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Pickup")
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Pickup", meta = (EditCondition = "PickupType == EBiohazardPickupType::KeyItem"))
	EBiohazardKeyType KeyItemType = EBiohazardKeyType::SpadeKey;

	virtual bool OnPlayerInteract_Implementation(ABiohazardCharacter* InteractingPlayer) override;
	virtual FText GetInteractionPrompt_Implementation() const override;
};
