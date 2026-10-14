#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BiohazardGameMode.generated.h"

UENUM(BlueprintType)
enum class EBiohazardGameModeType : uint8
{
	StoryEscape      UMETA(DisplayName = "Story Escape Mode"),
	MercenariesWaves UMETA(DisplayName = "The Mercenaries Wave Mode")
};

UCLASS()
class BIOHAZARDUNREAL_API ABiohazardGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABiohazardGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biohazard")
	EBiohazardGameModeType ActiveMode = EBiohazardGameModeType::StoryEscape;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard")
	int32 CurrentWave = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biohazard")
	int32 TotalScore = 0;

	UFUNCTION(BlueprintCallable, Category = "Biohazard")
	void AddScore(int32 Points);

	UFUNCTION(BlueprintCallable, Category = "Biohazard")
	void OnHelipadReached();
};
