#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/BiohazardInteractableInterface.h"
#include "Core/BiohazardTypes.h"
#include "BiohazardDoor.generated.h"

class UStaticMeshComponent;

UCLASS()
class BIOHAZARDUNREAL_API ABiohazardDoor : public AActor, public IBiohazardInteractableInterface
{
	GENERATED_BODY()

public:
	ABiohazardDoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Door")
	bool bRequiresKey = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Door", meta = (EditCondition = "bRequiresKey"))
	EBiohazardKeyType RequiredKey = EBiohazardKeyType::SpadeKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard|Door")
	bool bIsOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard|Door")
	float OpenAngle = 90.0f;

	virtual bool OnPlayerInteract_Implementation(ABiohazardCharacter* InteractingPlayer) override;
	virtual FText GetInteractionPrompt_Implementation() const override;

private:
	FRotator ClosedRotation;
	FRotator TargetRotation;
};
