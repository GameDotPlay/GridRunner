#include "FireProjectileComponent.h"

UFireProjectileComponent::UFireProjectileComponent()
{

}

void UFireProjectileComponent::CastAbility()
{
	Super::CastAbility();

	this->SpawnProjectile();
}

void UFireProjectileComponent::SpawnProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("Enter FireProjectileComponent::SpawnProjectile()"));

	if (ensureAlways(this->ProjectlileClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("In SpawnProjectile() ProjectileClass not null"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Cast<APawn>(this->GetOwner());

		FVector spawnLocation = this->GetOwner()->GetActorLocation();
		spawnLocation += this->GetOwner()->GetActorUpVector() * 50;
		FTransform SpawnTM = FTransform(spawnLocation);
		SpawnTM.SetRotation(this->GetOwner()->GetActorRotation().Quaternion());
		GetWorld()->SpawnActor<AActor>(this->ProjectlileClass, SpawnTM, SpawnParams);
	}

	UE_LOG(LogTemp, Warning, TEXT("Exit FireProjectileComponent::SpawnProjectile()"));
}
