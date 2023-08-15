#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class GRIDRUNNER_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AProjectileBase();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Base")
	UNiagaraSystem* ImpactEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Base")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Base")
	UProjectileMovementComponent* MoveComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectileBase")
	float MaxLifeTime;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void BeginPlay() override;

private:

	FTimerHandle NoHitKillTimer;

	UFUNCTION()
	void NoHitKillTimerElapsed();
};
