// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridRunnerCharacterBase.generated.h"

UCLASS()
class GRIDRUNNER_API AGridRunnerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGridRunnerCharacterBase();

	bool bIsIt = false;

	bool bIsPlayer = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CharacterIsIt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float XRotateSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float RunSpeed = 300.f;

private:	

};