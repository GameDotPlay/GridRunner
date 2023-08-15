#pragma once

#include "CoreMinimal.h"
#include "MagicCastComponentBase.h"
#include "ProjectileBase.h"
#include "FireProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIDRUNNER_API UFireProjectileComponent : public UMagicCastComponentBase
{
	GENERATED_BODY()

public:	

	UFireProjectileComponent();
	
	virtual void CastAbility() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectileBase> ProjectlileClass = nullptr;

private:

	void SpawnProjectile();

};
