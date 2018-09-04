// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//no need to protect ptr
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
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
	Barrel = BarrelToSet;
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

// Called from BP
void ATank::Fire()
{
	bool CanFire = (FPlatformTime::Seconds() - LastTime) >= ReloadTime;
	if (Barrel && ProjectileBP && CanFire)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBP, //Spawn的Actor, 在BP選擇了
				Barrel->GetSocketLocation(FName("Projectile")), //砲彈的出生位置
				Barrel->GetSocketRotation(FName("Projectil")) //砲彈的方向
			);
		Projectile->Launch(LaunchSpeed);
		LastTime = FPlatformTime::Seconds();
	}
}
	




