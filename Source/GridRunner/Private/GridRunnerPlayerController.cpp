#include "GridRunnerPlayerController.h"

void AGridRunnerPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		this->GetPawn()->EnableInput(this);
	}
	else
	{
		this->GetPawn()->DisableInput(this);
	}
}