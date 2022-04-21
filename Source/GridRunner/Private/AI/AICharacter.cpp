// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GridRunner/GridRunnerGameMode.h"

AAICharacter::AAICharacter()
{
    
}

void AAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    
    auto GameMode = Cast<AGridRunnerGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        GameMode->CacheOpponentCharacter(this);
    }
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = this->RunSpeed;
    this->bIsPlayer = false;
}

void AAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}