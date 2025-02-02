#pragma once

#include "CoreMinimal.h"
#include "GridRunnerCharacterBase.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UMaterialInstanceDynamic;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UAttributeComponent;
class UFireProjectileComponent;

UCLASS()
class GRIDRUNNER_API APlayerCharacter : public AGridRunnerCharacterBase
{
	GENERATED_BODY()

public:

	APlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OtherCharacterTouched(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* OpponentArrowIndicator = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	UAttributeComponent* AttributeComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	UFireProjectileComponent* FireProjectileComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float ArrowRadius = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float ArrowHeightOffset = 80.f;

	AGridRunnerCharacterBase* OpponentCharacter = nullptr;

	UMaterialInstanceDynamic* ArrowMaterial = nullptr;

	bool IsOpponentOnScreen();

	void UpdateArrowIndicator();

#pragma region Input

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) 
	UInputAction* MoveForwardAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveRightAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* FireProjectileAction = nullptr;

	void MoveForward(const FInputActionValue& Value);

	void MoveRight(const FInputActionValue& Value);

	void FireProjectile(const FInputActionValue& Value);

#pragma endregion
};
