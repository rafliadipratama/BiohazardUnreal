#include "Environment/BiohazardDoor.h"
#include "Characters/BiohazardCharacter.h"
#include "Framework/Components/BiohazardInventoryComponent.h"
#include "Components/StaticMeshComponent.h"

ABiohazardDoor::ABiohazardDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

void ABiohazardDoor::BeginPlay()
{
	Super::BeginPlay();
	ClosedRotation = GetActorRotation();
	TargetRotation = ClosedRotation;
}

void ABiohazardDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();
	if (!CurrentRotation.Equals(TargetRotation, 0.5f))
	{
		SetActorRotation(FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 4.0f));
	}
}

bool ABiohazardDoor::OnPlayerInteract_Implementation(ABiohazardCharacter* InteractingPlayer)
{
	if (!InteractingPlayer) return false;

	if (bIsOpen)
	{
		TargetRotation = ClosedRotation;
		bIsOpen = false;
		return true;
	}

	if (bRequiresKey)
	{
		if (InteractingPlayer->InventoryComponent && InteractingPlayer->InventoryComponent->HasKey(RequiredKey))
		{
			bRequiresKey = false;
			TargetRotation = ClosedRotation + FRotator(0.0f, OpenAngle, 0.0f);
			bIsOpen = true;
			return true;
		}
		return false;
	}

	TargetRotation = ClosedRotation + FRotator(0.0f, OpenAngle, 0.0f);
	bIsOpen = true;
	return true;
}

FText ABiohazardDoor::GetInteractionPrompt_Implementation() const
{
	if (bIsOpen) return FText::FromString(TEXT("Tutup Pintu [E]"));
	if (bRequiresKey) return FText::FromString(TEXT("Pintu Terkunci [E]"));
	return FText::FromString(TEXT("Buka Pintu [E]"));
}
