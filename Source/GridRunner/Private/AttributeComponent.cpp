#include "AttributeComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

UAttributeComponent::UAttributeComponent()
{
	this->BaseMaxMana = 100;
	this->CurrentMana = this->BaseMaxMana;
	this->MaxAllowedModifiedRunSpeed = 3;
}

void UAttributeComponent::SetBaseMaxRunSpeed(int32 newBaseRunSpeed)
{
	if (newBaseRunSpeed < 0)
	{
		this->BaseMaxRunSpeed = 0;
	}
	else
	{
		this->BaseMaxRunSpeed = newBaseRunSpeed;
	}
}

void UAttributeComponent::ApplyRunSpeedModifier(float modifier)
{
	if (ensureAlways(IsValid(this->MovementComponent)))
	{
		// Only allow up to double run speed modifier.
		this->MovementComponent->MaxWalkSpeed = FMath::Clamp(this->MovementComponent->MaxWalkSpeed * modifier, 0, BaseMaxRunSpeed * this->MaxAllowedModifiedRunSpeed);
	}
}

void UAttributeComponent::ResetBaseMaxRunSpeed()
{
	if (ensureAlways(IsValid(this->MovementComponent)))
	{
		this->MovementComponent->MaxWalkSpeed = this->BaseMaxRunSpeed;
	}
}

void UAttributeComponent::ApplyManaChange(int32 manaDelta)
{
	this->CurrentMana = FMath::Clamp(this->CurrentMana += manaDelta, 0, this->BaseMaxMana);
}

void UAttributeComponent::SetCurrentMana(int32 newCurrentMana)
{
	this->CurrentMana = FMath::Clamp(newCurrentMana, 0, this->BaseMaxMana);
}

void UAttributeComponent::SetBaseMaxMana(int32 newBaseMaxMana)
{
	if (newBaseMaxMana < 0)
	{
		this->BaseMaxMana = 0;
	}
	else
	{
		this->BaseMaxMana = newBaseMaxMana;
	}
}

int32 UAttributeComponent::GetBaseMaxRunSpeed() const
{
	return this->BaseMaxRunSpeed;
}

int32 UAttributeComponent::GetCurrentRunSpeed() const
{
	return this->CurrentRunSpeed;
}

int32 UAttributeComponent::GetBaseMaxMana() const
{
	return this->BaseMaxMana;
}

int32 UAttributeComponent::GetCurrentMana() const
{
	return this->CurrentMana;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the CharacterMovementComponent.
	this->MovementComponent = Cast<UCharacterMovementComponent>(this->GetOwner()->GetComponentByClass(TSubclassOf<UCharacterMovementComponent>()));

	if (ensureAlways(IsValid(this->MovementComponent)))
	{
		this->MovementComponent->MaxWalkSpeed = this->BaseMaxRunSpeed;
	}
	
	this->CurrentRunSpeed = this->BaseMaxRunSpeed;
}
