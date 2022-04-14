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

	UFUNCTION()
	void FlagCaptured(const AActor* ActorThatCaptured);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 PlayerFlags = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 OpponentFlags = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 FlagsREquiredToWin = 0;

protected:

	virtual void BeginPlay() override;

private:

	class APawn* PlayerCharacter = nullptr;
};