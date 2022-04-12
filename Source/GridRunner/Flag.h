// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flag.generated.h"

UCLASS()
class GRIDRUNNER_API AFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlag();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void FlagTouched(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere, Category = "Flag")
	class USphereComponent* SphereComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Flag")
	class UStaticMeshComponent* FlagMesh = nullptr;

	class UMaterialInstanceDynamic* FlagMaterial = nullptr;

	class AGridRunnerGameMode* GameMode = nullptr;

	class APawn* PlayerPawn = nullptr;

	FColor PlayerCaptured = FColor::Blue;

	FColor OpponentCaptured = FColor::Red;

	FColor Nuetral = FColor::White;
};