// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void SetAimCompRef(UTankAimingComponent* AimCompRef);


private:
	void AimTo();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirectionAndLineTrace(FVector2D CrossHairScreenLocation, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairLocationX = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairLocationY = 0.33333f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LineTraceRange = 1000000.0f;
	
};
