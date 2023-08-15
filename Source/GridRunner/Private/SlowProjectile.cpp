#include "SlowProjectile.h"
#include "Components/SphereComponent.h"
#include "AttributeComponent.h"

ASlowProjectile::ASlowProjectile()
{
	this->SphereComponent->SetSphereRadius(20.0f);
	this->SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASlowProjectile::OnActorOverlap);

	this->SlowMultiplier = 0.8f;
}

void ASlowProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && OtherActor != this->GetInstigator())
	{
		UAttributeComponent* AttributeComp = Cast<UAttributeComponent>(OtherActor->GetComponentByClass(UAttributeComponent::StaticClass()));
		if (IsValid(AttributeComp))
		{
			AttributeComp->ApplyRunSpeedModifier(this->SlowMultiplier);

			this->Explode();
		}
	}
}
