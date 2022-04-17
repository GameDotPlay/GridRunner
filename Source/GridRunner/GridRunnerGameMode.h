#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridRunnerGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFlagCaptured);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerCaptured);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpponentCaptured);

UCLASS(minimalapi)
class AGridRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnFlagCaptured OnFlagCaptured;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerCaptured OnPlayerCaptured;

	UPROPERTY(BlueprintAssignable)
	FOnOpponentCaptured OnOpponentCaptured;

	AGridRunnerGameMode();
	
	UFUNCTION()
	void FlagCaptured(const AActor* ActorThatCaptured);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 PlayerFlags = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 OpponentFlags = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	int32 FlagsRequiredToWin = 4;

protected:

	virtual void BeginPlay() override;

private:

	class APawn* PlayerCharacter = nullptr;

	void AssignIt(const AActor* ActorThatCaptured) const;
};