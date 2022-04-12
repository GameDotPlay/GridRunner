// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIOpponent.h"

// Sets default values
AAIOpponent::AAIOpponent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIOpponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIOpponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}