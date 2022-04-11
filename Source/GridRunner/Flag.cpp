// Fill out your copyright notice in the Description page of Project Settings.

#include "Flag.h"
#include "Components/SphereComponent.h"
#include "GridRunnerGameMode.h"

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
	
}

// Called every frame
void AFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}