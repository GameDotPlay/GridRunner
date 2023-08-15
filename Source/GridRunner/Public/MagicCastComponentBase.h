#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MagicCastComponentBase.generated.h"

class AProjectileBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIDRUNNER_API UMagicCastComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	

	UMagicCastComponentBase();

	virtual void CastAbility();

};
