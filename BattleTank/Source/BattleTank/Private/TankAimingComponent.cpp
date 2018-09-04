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
			StartLocation, //�j���f
			HitLocation, //CrossHair���۪���m
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
		
		if (HaveAimSolution)
		{
			auto AimDirection = LaunchVelocity.GetSafeNormal(); //�q�j����m��HitLocation��LookDirection
			MoveBarrel(AimDirection);
		}

	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //���o�j������l����(Pitch, Yaw, Roll)
	auto AimRotator = AimDirection.Rotation(); //�j���ݪ���V������(Pitch, Yaw, Roll)
	auto DeltaRotator = AimRotator - BarrelRotator; //�j���ݭn���ʪ����� 
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turrent->Rotate(DeltaRotator.Yaw);
}



	
