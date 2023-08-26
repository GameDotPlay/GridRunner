#include "AttributeComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

UAttributeComponent::UAttributeComponent()
{
	this->BaseMaxMana = 100;
	this->CurrentMana = this->BaseMaxMana;
	this->MaxAllowedModifiedRunSpeed = 3;
}

void UAttributeComponent::SetBaseMaxRunSpeed(const int32 newBaseRunSpeed)
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

void UAttributeComponent::ApplyRunSpeedModifier(const float modifier)
{
	if (ensureAlways(IsValid(this->MovementComponent)))
	{
		float minRunSpeed = this->BaseMaxRunSpeed * 0.5f;
		this->MovementComponent->MaxWalkSpeed = FMath::Clamp(this->MovementComponent->MaxWalkSpeed * modifier, minRunSpeed, BaseMaxRunSpeed * this->MaxAllowedModifiedRunSpeed);
	}
}

void UAttributeComponent::ResetBaseMaxRunSpeed()
{
	if (ensureAlways(IsValid(this->MovementComponent)))
	{
		this->MovementComponent->MaxWalkSpeed = this->BaseMaxRunSpeed;
	}
}

void UAttributeComponent::ApplyManaChange(const int32 manaDelta)
{
	this->CurrentMana = FMath::Clamp(this->CurrentMana += manaDelta, 0, this->BaseMaxMana);
}

void UAttributeComponent::SetCurrentMana(const int32 newCurrentMana)
{
	this->CurrentMana = FMath::Clamp(newCurrentMana, 0, this->BaseMaxMana);
}

void UAttributeComponent::SetBaseMaxMana(const int32 newBaseMaxMana)
{
	this->BaseMaxMana = newBaseMaxMana < 0 ? 0 : newBaseMaxMana;
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

int32 UAttributeComponent::AddFlag()
{
	this->OnFlagsChanged.Broadcast(this->CurrentFlagsCount);
	return this->CurrentFlagsCount + 1;
}

int32 UAttributeComponent::RemoveFlag()
{
	if (this->CurrentFlagsCount == 0)
	{
		return 0;
	}
	else
	{
		this->OnFlagsChanged.Broadcast(this->CurrentFlagsCount);
		return this->CurrentFlagsCount - 1;
	}
}

int32 UAttributeComponent::GetCurrentFlagsCount() const
{
	return this->CurrentFlagsCount;
}

bool UAttributeComponent::GetIsIt() const
{
	return this->bIsIt;
}

void UAttributeComponent::SetIsIt(const bool bPlayerIsIt)
{
	this->bIsIt = bPlayerIsIt;
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
