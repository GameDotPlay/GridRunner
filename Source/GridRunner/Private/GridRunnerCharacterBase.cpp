// Fill out your copyright notice in the Description page of Project Settings.

#include "GridRunnerCharacterBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGridRunnerCharacterBase::AGridRunnerCharacterBase()
{
 	this->CharacterIsIt = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterIsIt"));
	this->GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AGridRunnerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGridRunnerCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector MyLocation = GetActorLocation();
	this->CharacterIsIt->SetWorldLocation(FVector(MyLocation.X, MyLocation.Y, MyLocation.Z + 100.f));
	this->CharacterIsIt->AddWorldRotation(FRotator(0, this->XRotateSpeed * DeltaSeconds, 0));

	if (this->bIsIt)
	{
		this->CharacterIsIt->SetHiddenInGame(false);
	}
	else
	{
		this->CharacterIsIt->SetHiddenInGame(true);
	}
}