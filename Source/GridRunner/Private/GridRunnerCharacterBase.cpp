// Fill out your copyright notice in the Description page of Project Settings.

#include "GridRunnerCharacterBase.h"

// Sets default values
AGridRunnerCharacterBase::AGridRunnerCharacterBase()
{
 	this->CharacterIsIt = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterIsIt"));
}

// Called when the game starts or when spawned
void AGridRunnerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGridRunnerCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (this->bIsIt)
	{
		this->CharacterIsIt->bHiddenInGame = false;
		this->CharacterIsIt->AddWorldRotation(FRotator(0, this->XRotateSpeed * DeltaSeconds, 0));
	}
	else
	{
		this->CharacterIsIt->bHiddenInGame = true;
	}
}