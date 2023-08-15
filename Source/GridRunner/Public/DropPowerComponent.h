#pragma once

#include "CoreMinimal.h"
#include "MagicCastComponentBase.h"
#include "DropPowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIDRUNNER_API UDropPowerComponent : public UMagicCastComponentBase
{
	GENERATED_BODY()

public:	
	UDropPowerComponent();
	
	virtual void CastAbility() override;

};
