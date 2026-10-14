#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BiohazardInteractableInterface.generated.h"

class ABiohazardCharacter;

UINTERFACE(MinimalAPI, Blueprintable)
class UBiohazardInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class BIOHAZARDUNREAL_API IBiohazardInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool OnPlayerInteract(ABiohazardCharacter* InteractingPlayer);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionPrompt() const;
};
