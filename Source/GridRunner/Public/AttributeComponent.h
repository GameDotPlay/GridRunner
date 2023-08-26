#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFlagsChangedSignature, int32, NewFlags);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIDRUNNER_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(BlueprintAssignable)
	FFlagsChangedSignature OnFlagsChanged;

	UAttributeComponent();

	UFUNCTION(BlueprintCallable)
	void SetBaseMaxRunSpeed(const int32 newBaseRunSpeed);

	UFUNCTION(BlueprintCallable)
	void ApplyRunSpeedModifier(const float modifier);

	UFUNCTION(BlueprintCallable)
	void ResetBaseMaxRunSpeed();

	UFUNCTION(BlueprintCallable)
	void ApplyManaChange(const int32 manaDelta);

	UFUNCTION(BlueprintCallable)
	void SetCurrentMana(const int32 newCurrentMana);

	UFUNCTION(BlueprintCallable)
	void SetBaseMaxMana(const int32 newBaseMaxMana);

	UFUNCTION(BlueprintCallable)
	int32 GetBaseMaxRunSpeed() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentRunSpeed() const;

	UFUNCTION(BlueprintCallable)
	int32 GetBaseMaxMana() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentMana() const;

	UFUNCTION(BlueprintCallable)
	int32 AddFlag();

	UFUNCTION(BlueprintCallable)
	int32 RemoveFlag();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentFlagsCount() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsIt() const;

	UFUNCTION(BlueprintCallable)
	void SetIsIt(const bool bIsIt);

protected:

	virtual void BeginPlay() override;

private:

	UCharacterMovementComponent* MovementComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 BaseMaxMana;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 BaseMaxRunSpeed;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 MaxAllowedModifiedRunSpeed;

	int32 CurrentMana;

	int32 CurrentRunSpeed;

	int32 CurrentFlagsCount = 0;

	bool bIsIt = false;
};
