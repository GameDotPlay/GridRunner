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

	int32 PlayerFlags;
	int32 OpponentFlags;
	int32 FlagsREquiredToWin;
};