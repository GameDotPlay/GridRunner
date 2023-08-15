#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectBaseUtility.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AProjectileBase::AProjectileBase()
{
	this->SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->SphereComponent->SetCollisionProfileName("Projectile");
	this->SphereComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnActorHit);
	this->SetRootComponent(this->SphereComponent);

	this->MoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	this->MoveComponent->bRotationFollowsVelocity = true;
	this->MoveComponent->bInitialVelocityInLocalSpace = true;
	this->MoveComponent->ProjectileGravityScale = 0.0f;
	this->MoveComponent->InitialSpeed = 5000;

	this->MaxLifeTime = 3.0f;
}

void AProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	this->Explode();
}

void AProjectileBase::Explode_Implementation()
{
	if (ensure(IsValid(this)))
	{
		// This spawns the chosen effect on the owning WeaponMuzzle SceneComponent
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, this->ImpactEffect, this->GetActorLocation());
		this->Destroy();
	}
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(this->NoHitKillTimer, this, &AProjectileBase::NoHitKillTimerElapsed, this->MaxLifeTime);
}

void AProjectileBase::NoHitKillTimerElapsed()
{
	UE_LOG(LogTemp, Warning, TEXT("Enter AProjectileBase::NoHitKillTimerElapsped()"));
	this->Explode();
}
