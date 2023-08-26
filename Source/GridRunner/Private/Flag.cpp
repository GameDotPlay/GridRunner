#include "Flag.h"
#include "Components/SphereComponent.h"
#include "GridRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GridRunnerCharacterBase.h"

#define OUT

FFlagTouchedEvent AFlag::OnFlagTouched;

AFlag::AFlag()
{
	this->SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->SetRootComponent(this->SphereComponent);

	this->FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	this->FlagMesh->SetupAttachment(this->RootComponent);

	this->OwningPlayer = nullptr;
}

void AFlag::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	this->SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFlag::FlagTouched);
	this->FlagMaterial = UMaterialInstanceDynamic::Create(this->FlagMesh->GetMaterial(0), this);

	this->SetColor(this->NeutralColor);
}

void AFlag::SetColor(const FLinearColor newColor)
{
	this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), newColor);

	this->FlagMesh->SetMaterial(0, this->FlagMaterial);

	this->CurrentColor = newColor;
}

AActor* AFlag::GetOwningPlayer() const
{
	return this->OwningPlayer;
}

FLinearColor AFlag::GetCurrentColor() const
{
	return this->CurrentColor;
}

void AFlag::FlagTouched(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
	{
		return; // OtherActor is null.
	}

	auto CharacterThatTouched = Cast<AGridRunnerCharacterBase>(OtherActor);
	if (!IsValid(CharacterThatTouched))
	{
		return; // OtherActor is not a player character. Do nothing.
	}

	if (OtherActor == this->OwningPlayer)
	{
		return; // This player already owns us. Do nothing.
	}

	AFlag::OnFlagTouched.ExecuteIfBound(OtherActor, this);
}