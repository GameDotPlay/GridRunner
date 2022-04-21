// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridRunnerGameMode.h"
#include "GridRunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "AI/AICharacter.h"

AGridRunnerGameMode::AGridRunnerGameMode()
{
	
}

void AGridRunnerGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    this->PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

    ensureMsgf(this->PlayerCharacter, TEXT("GameMode::PlayerCharacter is null."));
    ensureMsgf(this->OpponentCharacter, TEXT("GameMode::OpponentCharacter is null"));
}

void AGridRunnerGameMode::FlagCaptured(const AActor* ActorThatCaptured)
{
    if(!ensure(this->PlayerCharacter && this->OpponentCharacter && ActorThatCaptured))
    {
        return;
    }

    // Nobody has captured any flags yet. Set who is IT.
    if (this->PlayerFlags == 0 && this->OpponentFlags == 0)
    {
        if (ActorThatCaptured == this->PlayerCharacter)
        {
            this->PlayerCharacter->bIsIt = false;
            this->OpponentCharacter->bIsIt = true;
        }
        else if (ActorThatCaptured == this->OpponentCharacter)
        {
            this->PlayerCharacter->bIsIt = true;
            this->OpponentCharacter->bIsIt = false;
        }
    }

    if (ActorThatCaptured == this->PlayerCharacter)
    {
        this->PlayerFlags++;
        this->OnPlayerFlagsChanged.Broadcast();

        if (this->OpponentFlags > 0)
        {
            this->OpponentFlags--;
            this->OnOpponentFlagsChanged.Broadcast();
        }
    }
    else if (ActorThatCaptured == this->OpponentCharacter)
    {
        this->OpponentFlags++;
        this->OnOpponentFlagsChanged.Broadcast();

        if (this->PlayerFlags > 0)
        {
            this->PlayerFlags--;
            this->OnPlayerFlagsChanged.Broadcast();
        }
    }
}

void AGridRunnerGameMode::CacheOpponentCharacter(AAICharacter* Opponent)
{
    if (ensureMsgf(Opponent, TEXT("Opponent reference is null.")))
    {
        this->OpponentCharacter = Opponent;
    }
}