#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIDRUNNER_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttributeComponent();

	UFUNCTION(BlueprintCallable)
	void SetBaseMaxRunSpeed(int32 newBaseRunSpeed);

	UFUNCTION(BlueprintCallable)
	void ApplyRunSpeedModifier(float modifier);

	UFUNCTION(BlueprintCallable)
	void ResetBaseMaxRunSpeed();

	UFUNCTION(BlueprintCallable)
	void ApplyManaChange(int32 manaDelta);

	UFUNCTION(BlueprintCallable)
	void SetCurrentMana(int32 newCurrentMana);

	UFUNCTION(BlueprintCallable)
	void SetBaseMaxMana(int32 newBaseMaxMana);

	UFUNCTION(BlueprintCallable)
	int32 GetBaseMaxRunSpeed() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentRunSpeed() const;

	UFUNCTION(BlueprintCallable)
	int32 GetBaseMaxMana() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentMana() const;

protected:

	virtual void BeginPlay() override;

private:

	UCharacterMovementComponent* MovementComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 BaseMaxMana;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 MaxAllowedModifiedRunSpeed;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 CurrentMana;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 BaseMaxRunSpeed;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 CurrentRunSpeed;
};
