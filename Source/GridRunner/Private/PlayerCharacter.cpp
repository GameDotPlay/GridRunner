// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation

	OpponentArrowIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OpponentArrowIndicator"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 1200.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = this->RunSpeed;
	this->bIsPlayer = true;

	// Bind method to OnComponentBeginOverlap.
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OtherCharacterTouched);

	// Get reference to opponent character.
	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridRunnerCharacterBase::StaticClass(), Characters);
	for (int i = 0; i < Characters.Num(); i++)
	{
		// Iterate through all actors returned (Should only be 2). First one to not be player is the opponent.
		auto Opponent = Cast<AGridRunnerCharacterBase>(Characters[i]);
		if (!Opponent->bIsPlayer)
		{
			this->OpponentCharacter = Opponent;
			break;
		}
	}

	// Get reference to the arrow material.
	this->ArrowMaterial = UMaterialInstanceDynamic::Create(this->OpponentArrowIndicator->GetMaterial(0), this);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->UpdateArrowIndicator();
}

bool APlayerCharacter::IsOpponentOnScreen()
{
	APlayerController* PlayerController = Cast<APlayerController>(this->GetController());
	FVector2D ScreenPosition;
	FVector OpponentOrigin;
	FVector BoxExtent;
	this->OpponentCharacter->GetActorBounds(false, OpponentOrigin, BoxExtent, false);
	UGameplayStatics::ProjectWorldToScreen(PlayerController, OpponentOrigin, ScreenPosition);

	int32 ViewportSizeX;
	int32 ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	return ScreenPosition.X + BoxExtent.X > 0 && ScreenPosition.Y + BoxExtent.Y > 0 && ScreenPosition.X - BoxExtent.X < (int32)ViewportSizeX && ScreenPosition.Y - BoxExtent.Y < (int32)ViewportSizeY;
}

void APlayerCharacter::UpdateArrowIndicator()
{
	if (IsOpponentOnScreen())
	{
		this->OpponentArrowIndicator->SetHiddenInGame(true);
	}
	else
	{
		this->OpponentArrowIndicator->SetHiddenInGame(false);
	}

	if (!this->OpponentArrowIndicator->bHiddenInGame)
	{
		FVector LineToOpponent = this->OpponentCharacter->GetActorLocation() - this->GetActorLocation();
		LineToOpponent.Normalize();
		LineToOpponent *= this->ArrowRadius;
		FRotator YawOffset(0.f, 0.f, 0.f);
		if (this->bIsIt)
		{
			this->ArrowMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), FColor::Green);
			YawOffset.Yaw = 180.f;
		}
		else
		{
			this->ArrowMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), FColor::Red);
		}

		FVector HeightOffset = FVector(0.f, 0.f, this->ArrowHeightOffset);
		this->OpponentArrowIndicator->SetWorldRotation(LineToOpponent.Rotation() + YawOffset);
		this->OpponentArrowIndicator->SetWorldLocation(this->GetActorLocation() + LineToOpponent + HeightOffset);
		this->OpponentArrowIndicator->SetMaterial(0, this->ArrowMaterial);
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is forward.
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector.
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Add movement in that direction.
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// Find out which way is right.
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// Get right vector. 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// Add movement in that direction.
		AddMovementInput(Direction, Value);
	}
}

// Called to bind functionality to input.
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::OtherCharacterTouched(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ensure(OtherActor))
	{
		return; // OtherActor is null.
	}

	auto OtherCharacter = Cast<AGridRunnerCharacterBase>(OtherActor);
	if (!OtherCharacter)
	{
		return; // OtherActor is not the player or the opponent. Do nothing...for now.
	}

	if (!this->bIsIt && !OtherCharacter->bIsIt)
	{
		return; // Neither character is IT yet. Do nothing.
	}

	OtherCharacter->bIsIt = !OtherCharacter->bIsIt;
	this->bIsIt = !this->bIsIt;
}