// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declartion
class UTankAimingComponent; 
class UTankBarrel;
class UTankTurrent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called to TankAimingComponent
	void AimTo(FVector HitLocation); 
	
private:
	UTankAimingComponent* TankAimingComponent = nullptr;

	// Called to TankAimingComponent
	UFUNCTION(BlueprintCallAble, Category = Setup)
	void SetBarrelComponent(UTankBarrel* BarrelToSet);
	
	// Called to TankAimingComponent
	UFUNCTION(BlueprintCallAble, Category = Setup)
	void SetTurrentComponent(UTankTurrent* TurrentToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 40000;

};
