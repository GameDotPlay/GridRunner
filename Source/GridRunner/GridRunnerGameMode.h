// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridRunnerGameMode.generated.h"

UCLASS(minimalapi)
class AGridRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGridRunnerGameMode();

	void FlagCaptured(const AActor* ActorThatCaptured);

protected:

	virtual void BeginPlay() override;

private:

	class APawn* PlayerCharacter = nullptr;
	int32 PlayerFlags = 0;
	int32 OpponentFlags = 0;
	int32 FlagsREquiredToWin = 0;
};