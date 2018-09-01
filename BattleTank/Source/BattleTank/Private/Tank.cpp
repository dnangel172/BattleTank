// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//no need to protect ptr
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called to TankAimingComponent, Called from BP
void ATank::SetBarrelComponent(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelComponent(BarrelToSet);
}

// Called to TankAimingComponent, Called from BP
void ATank::SetTurrentComponent(UTankTurrent* TurrentToSet)
{
	TankAimingComponent->SetTurrentComponent(TurrentToSet);
}

// Called to TankAimingComponent
void ATank::AimTo(FVector HitLocation)
{
	TankAimingComponent->AimTo(HitLocation, LaunchSpeed);
}




