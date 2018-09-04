// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declartion
class UTankAimingComponent; 
class UTankBarrel;
class UTankTurrent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called to TankAimingComponent
	void AimTo(FVector HitLocation);

	// Called from BP
	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();
	
private:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* Barrel = nullptr;
	
	// Called to TankAimingComponent from BP
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelComponent(UTankBarrel* BarrelToSet);
	
	// Called to TankAimingComponent from BP
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurrentComponent(UTankTurrent* TurrentToSet);

	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float ReloadTime = 3.0f;

	//¦bBP¿ï¾ÜFireªºActor
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBP;

	double LastTime = 0;

	
};
