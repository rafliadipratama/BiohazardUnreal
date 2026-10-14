#include "Core/BiohazardGameMode.h"
#include "Characters/BiohazardCharacter.h"

ABiohazardGameMode::ABiohazardGameMode()
{
	DefaultPawnClass = ABiohazardCharacter::StaticClass();
}

void ABiohazardGameMode::AddScore(int32 Points)
{
	TotalScore += Points;
}

void ABiohazardGameMode::OnHelipadReached()
{
	// Extraction gate opened, trigger victory sequence
}
