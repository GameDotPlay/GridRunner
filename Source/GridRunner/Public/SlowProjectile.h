// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "SlowProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GRIDRUNNER_API ASlowProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:

	ASlowProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Slow Projectile")
	float SlowMultiplier;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
