// Fill out your copyright notice in the Description page of Project Settings.

#include "Flag.h"
#include "Components/SphereComponent.h"
#include "GridRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"

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
	this->PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	this->FlagMaterial = UMaterialInstanceDynamic::Create(this->FlagMesh->GetMaterial(0), this);
}

void AFlag::FlagTouched(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<APawn>(OtherActor))
	{
		return; // Actor is not the player or the opponent. Do nothing.
	}

	FLinearColor CurrentFlagColor;
	FHashedMaterialParameterInfo MaterialParamterInfo(FName(TEXT("BaseColor")));
	this->FlagMesh->GetMaterial(0)->GetVectorParameterValue(MaterialParamterInfo, OUT CurrentFlagColor);
	this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), CurrentFlagColor);

	if (!this->PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn null"));
		return;
	}

	if (!OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor null"));
		return;
	}

	if (OtherActor == this->PlayerPawn) // Player touched flag.
	{
		if (CurrentFlagColor == this->PlayerCaptured)
		{
			return; // Flag is already controlled by player. Do nothing.
		}

		this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), this->PlayerCaptured);
	}
	else // Opponent touched flag.
	{
		if (CurrentFlagColor == this->OpponentCaptured)
		{
			return; // Flag is already controlled by opponent. Do nothing.
		}

		this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), this->OpponentCaptured);
	}

	this->FlagMesh->SetMaterial(0, this->FlagMaterial);
	this->GameMode->FlagCaptured(OtherActor);
}