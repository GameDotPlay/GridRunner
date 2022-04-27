// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridRunnerGameMode.generated.h"

class AAICharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerFlagsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpponentFlagsChanged);

UCLASS(minimalapi)
class AGridRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGridRunnerGameMode();

	void FlagCaptured(const AActor* ActorThatCaptured);

	UPROPERTY(BlueprintAssignable)
	FOnPlayerFlagsChanged OnPlayerFlagsChanged;

	UPROPERTY(BlueprintAssignable)
	FOnOpponentFlagsChanged OnOpponentFlagsChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 PlayerFlags = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 OpponentFlags = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 FlagsRequiredToWin = 5;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:

	class AGridRunnerCharacterBase* PlayerCharacter = nullptr;
	class AGridRunnerCharacterBase* OpponentCharacter = nullptr;

	class AGridRunnerPlayerController* PlayerController = nullptr;

	void HandleStart();

	float StartDelay = 3.f;
};