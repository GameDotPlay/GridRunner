// Fill out your copyright notice in the Description page of Project Settings.

#include "Flag.h"
#include "Components/SphereComponent.h"
#include "GridRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GridRunnerCharacterBase.h"

#define OUT

// Sets default values
AFlag::AFlag()
{
	this->SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->SetRootComponent(this->SphereComponent);

	this->FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	this->FlagMesh->SetupAttachment(this->RootComponent);
}

// Called when the game starts or when spawned
void AFlag::BeginPlay()
{
	Super::BeginPlay();

	this->GameMode = Cast<AGridRunnerGameMode>(UGameplayStatics::GetGameMode(this));
	this->SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFlag::FlagTouched);
	this->FlagMaterial = UMaterialInstanceDynamic::Create(this->FlagMesh->GetMaterial(0), this);
}

void AFlag::FlagTouched(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ensure(OtherActor))
	{
		return; // OtherActor is null.
	}

	auto CharacterThatTouched = Cast<AGridRunnerCharacterBase>(OtherActor);
	if (!CharacterThatTouched)
	{
		return; // Actor is not the player or the opponent. Do nothing.
	}

	FLinearColor CurrentFlagColor;
	FHashedMaterialParameterInfo MaterialParamterInfo(FName(TEXT("BaseColor")));
	this->FlagMesh->GetMaterial(0)->GetVectorParameterValue(MaterialParamterInfo, OUT CurrentFlagColor);
	this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), CurrentFlagColor);

	if (CharacterThatTouched->bIsPlayer) // Player touched flag.
	{
		if (CharacterThatTouched->bIsIt || CurrentFlagColor == this->PlayerCaptured)
		{
			return; // Player is "IT" or they already have this flag. Do nothing.
		}

		this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), this->PlayerCaptured);
	}
	else // Opponent touched flag.
	{
		if (CharacterThatTouched->bIsIt || CurrentFlagColor == this->OpponentCaptured)
		{
			return; // Opponent is "IT" or they already have this flag. Do nothing.
		}

		this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), this->OpponentCaptured);
	}

	this->FlagMesh->SetMaterial(0, this->FlagMaterial);
	this->GameMode->FlagCaptured(OtherActor);
}