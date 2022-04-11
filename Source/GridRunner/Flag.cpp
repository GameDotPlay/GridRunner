// Fill out your copyright notice in the Description page of Project Settings.

#include "Flag.h"
#include "Components/SphereComponent.h"
#include "GridRunnerGameMode.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AFlag::AFlag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->SetRootComponent(this->SphereComponent);

	this->FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	this->FlagMesh->SetupAttachment(this->RootComponent);
}

// Called when the game starts or when spawned
void AFlag::BeginPlay()
{
	Super::BeginPlay();

	this->FlagMaterial = UMaterialInstanceDynamic::Create(this->FlagMesh->GetMaterial(0),this);
	
	this->SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFlag::FlagClaimed); 
}

// Called every frame
void AFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlag::FlagClaimed(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!this->FlagMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("FlagMaterial is null"));
		return;
	}

	this->FlagMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), FColor::Red);
	UE_LOG(LogTemp, Warning, TEXT("In FlagClaimed()"));
}