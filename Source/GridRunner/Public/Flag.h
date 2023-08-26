#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flag.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

DECLARE_DELEGATE_TwoParams(FFlagTouchedEvent, AActor*, AFlag*);

UCLASS()
class GRIDRUNNER_API AFlag : public AActor
{
	GENERATED_BODY()
	
public:

	AFlag();

	static FFlagTouchedEvent OnFlagTouched;

	void SetColor(const FLinearColor newColor);

	AActor* GetOwningPlayer() const;

	FLinearColor GetCurrentColor() const;

protected:

	virtual void PostInitializeComponents() override;

private:

	UFUNCTION()
	void FlagTouched(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Flag")
	USphereComponent* SphereComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Flag")
	UStaticMeshComponent* FlagMesh = nullptr;

	UMaterialInstanceDynamic* FlagMaterial = nullptr;

	FLinearColor CurrentColor;

	FLinearColor NeutralColor = FLinearColor::White;

	AActor* OwningPlayer = nullptr;
};