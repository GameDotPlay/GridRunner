// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridRunnerCharacterBase.h"
#include "PlayerCharacter.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class GRIDRUNNER_API APlayerCharacter : public AGridRunnerCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OtherCharacterTouched(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* OpponentArrowIndicator;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float ArrowRadius = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float ArrowHeightOffset = 80.f;

	AGridRunnerCharacterBase* OpponentCharacter;

	UMaterialInstanceDynamic* ArrowMaterial;

	bool IsOpponentOnScreen();

	void UpdateArrowIndicator();
};
