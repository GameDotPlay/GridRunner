// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GridRunnerCharacterBase.h"
#include "GridRunnerPlayerController.h"

AGridRunnerGameMode::AGridRunnerGameMode()
{
	
}

void AGridRunnerGameMode::BeginPlay()
{
    Super::BeginPlay();
    
	// Get reference to player and opponent characters.
	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridRunnerCharacterBase::StaticClass(), Characters);
	for (int i = 0; i < Characters.Num(); i++)
	{
		// Iterate through all actors returned (Should only be 2). First one to not be player is the opponent.
		auto Character = Cast<AGridRunnerCharacterBase>(Characters[i]);
		if (Character->bIsPlayer)
		{
			this->PlayerCharacter = Character;
		}
        else
        {
            this->OpponentCharacter = Character;
        }
	}

    ensureMsgf(this->PlayerCharacter, TEXT("GameMode::PlayerCharacter is null."));
    ensureMsgf(this->OpponentCharacter, TEXT("GameMode::OpponentCharacter is null"));

    this->PlayerController = Cast<AGridRunnerPlayerController>(this->PlayerCharacter->GetController());

    ensureMsgf(this->PlayerController, TEXT("GameMode::PlayerController is null"));

    this->HandleStart();
}

void AGridRunnerGameMode::HandleStart()
{
    // Freeze any player input.
    this->PlayerController->SetPlayerEnabledState(false);

    // Activate timer for 3 second countdown.
    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(this->PlayerController, &AGridRunnerPlayerController::SetPlayerEnabledState, true);

    this->StartGame();
    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, this->StartDelay, false);
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