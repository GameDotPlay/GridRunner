#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/UObjectBaseUtility.h>

AProjectileBase::AProjectileBase()
{
	this->SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->SphereComponent->SetCollisionProfileName("Projectile");
	this->SphereComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnActorHit);
	this->SetRootComponent(this->SphereComponent);

	this->EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComponent"));
	this->EffectComponent->SetupAttachment(this->RootComponent);

	this->MoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	this->MoveComponent->bRotationFollowsVelocity = true;
	this->MoveComponent->bInitialVelocityInLocalSpace = true;
	this->MoveComponent->ProjectileGravityScale = 0.0f;
	this->MoveComponent->InitialSpeed = 8000;
}

void AProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	this->Explode();
}

void AProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, this->ImpactVFX, this->GetActorLocation(), this->GetActorRotation());

		this->Destroy();
	}
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
