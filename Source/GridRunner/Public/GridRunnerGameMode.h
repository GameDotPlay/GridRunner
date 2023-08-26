#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridRunnerGameMode.generated.h"

class AAICharacter;
class AGridRunnerCharacterBase;
class AFlag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerFlagsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpponentFlagsChanged);

UCLASS(minimalapi)
class AGridRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGridRunnerGameMode();

	void FlagTouched(const AActor* ActorThatTouched, const AFlag* FlagTouched);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags")
	int32 FlagsRequiredToWin = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags")
	int32 TotalFlags = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	float StartDelay = 3.f;

protected:

	virtual void BeginPlay() override;

private:

	TArray<AGridRunnerCharacterBase*> Players;

	void StartRound();

	void SetPlayerInputState(const bool bEnabled);

	void EnablePlayerInput();

	UFUNCTION()
	void ProcessFlagTouched(AActor* ActorThatTouched, AFlag* FlagTouched);

	int32 FreeFlags = 0;
};