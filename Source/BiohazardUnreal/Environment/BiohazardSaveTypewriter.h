#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/BiohazardInteractableInterface.h"
#include "BiohazardSaveTypewriter.generated.h"

class UStaticMeshComponent;

UCLASS()
class BIOHAZARDUNREAL_API ABiohazardSaveTypewriter : public AActor, public IBiohazardInteractableInterface
{
	GENERATED_BODY()

public:
	ABiohazardSaveTypewriter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TypewriterMesh;

	virtual bool OnPlayerInteract_Implementation(ABiohazardCharacter* InteractingPlayer) override;
	virtual FText GetInteractionPrompt_Implementation() const override;
};
