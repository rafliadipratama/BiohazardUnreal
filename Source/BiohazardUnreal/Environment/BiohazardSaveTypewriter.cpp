#include "Environment/BiohazardSaveTypewriter.h"
#include "Characters/BiohazardCharacter.h"
#include "Framework/Components/BiohazardHealthComponent.h"
#include "Components/StaticMeshComponent.h"

ABiohazardSaveTypewriter::ABiohazardSaveTypewriter()
{
	PrimaryActorTick.bCanEverTick = false;

	TypewriterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TypewriterMesh"));
	RootComponent = TypewriterMesh;
}

bool ABiohazardSaveTypewriter::OnPlayerInteract_Implementation(ABiohazardCharacter* InteractingPlayer)
{
	if (!InteractingPlayer) return false;

	// Resident Evil Safe Room: restores battery & cures poison
	InteractingPlayer->FlashlightBattery = 100.0f;
	if (InteractingPlayer->HealthComponent)
	{
		InteractingPlayer->HealthComponent->SetPoisoned(false);
	}
	return true;
}

FText ABiohazardSaveTypewriter::GetInteractionPrompt_Implementation() const
{
	return FText::FromString(TEXT("Gunakan Mesin Tik (Save & Pulihkan Baterai) [E]"));
}
