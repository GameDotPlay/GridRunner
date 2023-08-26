#include "GridRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GridRunnerCharacterBase.h"
#include "GridRunnerPlayerController.h"
#include "GridRunnerCharacterBase.h"
#include "AttributeComponent.h"
#include "Flag.h"

AGridRunnerGameMode::AGridRunnerGameMode()
{
    
}

void AGridRunnerGameMode::BeginPlay()
{
    Super::BeginPlay();

    AFlag::OnFlagTouched.BindUObject(this, &AGridRunnerGameMode::ProcessFlagTouched);
    
	// Get references to all players in the game, human and AI.
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridRunnerCharacterBase::StaticClass(), Actors);
	for (size_t i = 0; i < Actors.Num(); i++)
	{
		// Iterate through all actors returned and cache references to all players
		auto Character = Cast<AGridRunnerCharacterBase>(Actors[i]);
        this->Players.Add(Character);
	}

    this->StartRound();
}

void AGridRunnerGameMode::StartRound()
{
    // Freeze input for all players.
    for (size_t i = 0; i < this->Players.Num(); i++)
    {
        this->SetPlayerInputState(false);
    }

    // Activate timer start round countdown.
    FTimerHandle StartRoundTimerHandle;
    this->GetWorldTimerManager().SetTimer(StartRoundTimerHandle, this, &AGridRunnerGameMode::EnablePlayerInput, this->StartDelay);
}

void AGridRunnerGameMode::SetPlayerInputState(const bool bEnabled)
{
    for (size_t i = 0; i < this->Players.Num(); i++)
    {
        AGridRunnerPlayerController* Controller = Cast<AGridRunnerPlayerController>(this->Players[i]->GetController());
        Controller->SetPlayerEnabledState(bEnabled);
    }
}

void AGridRunnerGameMode::EnablePlayerInput()
{
    for (size_t i = 0; i < this->Players.Num(); i++)
    {
        AGridRunnerPlayerController* Controller = Cast<AGridRunnerPlayerController>(this->Players[i]->GetController());
        Controller->SetPlayerEnabledState(true);
    }
}

void AGridRunnerGameMode::ProcessFlagTouched(AActor* ActorThatTouched, AFlag* FlagTouched)
{
    UE_LOG(LogTemp, Warning, TEXT("Broadcast worked"));
}

void AGridRunnerGameMode::FlagTouched(const AActor* ActorThatTouched, const AFlag* FlagTouched)
{
    UAttributeComponent* PlayerAttributes = Cast<UAttributeComponent>(ActorThatTouched->GetComponentByClass(TSubclassOf<UAttributeComponent>()));

    if (!IsValid(PlayerAttributes))
    {
        return;
    }

    // Nobody has captured any flags yet. Set who is IT.
    if (this->FreeFlags == this->TotalFlags)
    {   
        PlayerAttributes->SetIsIt(true);
        PlayerAttributes->AddFlag();
        return;
    }
    else
    {

    }
}