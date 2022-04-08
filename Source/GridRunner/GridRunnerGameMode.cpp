// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridRunnerGameMode.h"
#include "GridRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGridRunnerGameMode::AGridRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
