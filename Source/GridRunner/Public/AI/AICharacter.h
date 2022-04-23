// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridRunnerCharacterBase.h"
#include "AICharacter.generated.h"

UCLASS()
class GRIDRUNNER_API AAICharacter : public AGridRunnerCharacterBase
{
	GENERATED_BODY()
	
public:

	// Sets default values for this character's properties
	AAICharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
