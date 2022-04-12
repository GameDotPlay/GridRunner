// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/OpponentAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AOpponentAIController::BeginPlay()
{
    Super::BeginPlay();

    this->RunBehaviorTree(this->BehaviorTree);

    APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
    if (Player)
    {
        this->GetBlackboardComponent()->SetValueAsVector("MoveToLocation", Player->GetActorLocation());
    }
}