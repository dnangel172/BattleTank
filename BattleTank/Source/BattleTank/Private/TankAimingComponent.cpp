// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurrent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called from Tank
void UTankAimingComponent::SetBarrelComponent(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

// Called from Tank
void UTankAimingComponent::SetTurrentComponent(UTankTurrent* TurrentToSet)
{
	if (!TurrentToSet) { return; }
	Turrent = TurrentToSet;
}

// Called from Tank 
void UTankAimingComponent::AimTo(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; } //prt protect
	{
		FVector LaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			LaunchVelocity, //out parameter	
			StartLocation, //大砲口
			HitLocation, //CrossHair指著的位置
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
		
		if (HaveAimSolution)
		{
			auto AimDirection = LaunchVelocity.GetSafeNormal(); //從大砲位置到HitLocation的LookDirection
			MoveBarrel(AimDirection);
		}

	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //取得大砲的初始角度(Pitch, Yaw, Roll)
	auto AimRotator = AimDirection.Rotation(); //大砲看的方向的角度(Pitch, Yaw, Roll)
	auto DeltaRotator = AimRotator - BarrelRotator; //大砲需要移動的角度 
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turrent->Rotate(DeltaRotator.Yaw);
}



	
