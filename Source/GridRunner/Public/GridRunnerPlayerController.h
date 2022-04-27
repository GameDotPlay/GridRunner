#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GridRunnerPlayerController.generated.h"

UCLASS()
class GRIDRUNNER_API AGridRunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetPlayerEnabledState(bool bPlayerEnabled);
	
};