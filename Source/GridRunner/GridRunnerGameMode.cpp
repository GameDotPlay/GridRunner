// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridRunnerGameMode.h"
#include "GridRunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GridRunnerCharacter.h"

AGridRunnerGameMode::AGridRunnerGameMode()
{
	
}

void AGridRunnerGameMode::BeginPlay()
{
    this->PlayerCharacter = UGameplayStatics::GetPlayerPawn(this, 0);
}

void AGridRunnerGameMode::FlagCaptured(const AActor* ActorThatCaptured)
{
    if (ActorThatCaptured == this->PlayerCharacter)
    {
        this->PlayerFlags++;

        if (this->OpponentFlags > 0)
        {
            this->OpponentFlags--;
        }
    }
    else
    {
        this->OpponentFlags++;

        if (this->PlayerFlags > 0)
        {
            this->OpponentFlags--;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Player: %i | Opponent: %i"), this->PlayerFlags, this->OpponentFlags);
}