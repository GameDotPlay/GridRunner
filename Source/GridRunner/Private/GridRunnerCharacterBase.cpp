// Fill out your copyright notice in the Description page of Project Settings.

#include "GridRunnerCharacterBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGridRunnerCharacterBase::AGridRunnerCharacterBase()
{
 	this->CharacterIsIt = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterIsIt"));
}

// Called when the game starts or when spawned
void AGridRunnerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGridRunnerCharacterBase::OtherCharacterTouched);
}

void AGridRunnerCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (this->bIsIt)
	{
		this->CharacterIsIt->bHiddenInGame = false;
		this->CharacterIsIt->SetWorldLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100.f));
		this->CharacterIsIt->AddWorldRotation(FRotator(0, this->XRotateSpeed * DeltaSeconds, 0));
	}
	else
	{
		this->CharacterIsIt->bHiddenInGame = true;
	}
}

void AGridRunnerCharacterBase::OtherCharacterTouched(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ensure(OtherActor))
	{
		return; // OtherActor is null.
	}

	if (!Cast<AGridRunnerCharacterBase>(OtherActor))
	{
		return; // OtherActor is not the player or the opponent. Do nothing...for now.
	}

	if (Cast<AGridRunnerCharacterBase>(OtherActor)->bIsIt) // We got tagged.
	{
		Cast<AGridRunnerCharacterBase>(OtherActor)->bIsIt = false;
		this->bIsIt = true;
	}
	else
	{
		Cast<AGridRunnerCharacterBase>(OtherActor)->bIsIt = true;
		this->bIsIt = false;
	}
}