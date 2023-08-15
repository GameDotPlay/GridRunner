#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "AttributeComponent.h"
#include "FireProjectileComponent.h"

APlayerCharacter::APlayerCharacter()
{
	this->bIsPlayer = true;

	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	this->SpringArmComponent->SetupAttachment(RootComponent);

	this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	this->FollowCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	this->OpponentArrowIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OpponentArrowIndicator"));

	this->AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));

	this->FireProjectileComponent = CreateDefaultSubobject<UFireProjectileComponent>(TEXT("FireProjectileComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 1200.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(this->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(this->DefaultMappingContext, 0);
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = this->RunSpeed;

	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OtherCharacterTouched);

	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridRunnerCharacterBase::StaticClass(), Characters);
	for (int i = 0; i < Characters.Num(); i++)
	{
		auto Opponent = Cast<AGridRunnerCharacterBase>(Characters[i]);
		if (!Opponent->bIsPlayer)
		{
			this->OpponentCharacter = Opponent;
			break;
		}
	}

	this->ArrowMaterial = UMaterialInstanceDynamic::Create(this->OpponentArrowIndicator->GetMaterial(0), this);
}

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

void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	float inputValue = Value.Get<float>();
	if ((Controller != nullptr) && (inputValue != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		this->AddMovementInput(Direction, inputValue);
	}
}

void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	float inputValue = Value.Get<float>();
	if ( (Controller != nullptr) && (inputValue != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Direction, inputValue);
	}
}

void APlayerCharacter::FireProjectile(const FInputActionValue& Value)
{
	this->FireProjectileComponent->CastAbility();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(this->MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);

		EnhancedInputComponent->BindAction(this->MoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);

		EnhancedInputComponent->BindAction(this->FireProjectileAction, ETriggerEvent::Triggered, this, &APlayerCharacter::FireProjectile);
	}
}

void APlayerCharacter::OtherCharacterTouched(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ensure(OtherActor))
	{
		return;
	}

	auto OtherCharacter = Cast<AGridRunnerCharacterBase>(OtherActor);
	if (!OtherCharacter)
	{
		return;
	}

	if (!this->bIsIt && !OtherCharacter->bIsIt)
	{
		return;
	}

	OtherCharacter->bIsIt = !OtherCharacter->bIsIt;
	this->bIsIt = !this->bIsIt;
}
