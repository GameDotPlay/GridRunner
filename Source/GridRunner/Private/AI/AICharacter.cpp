// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAICharacter::AAICharacter()
{
    
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = this->RunSpeed;
}

void AAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}