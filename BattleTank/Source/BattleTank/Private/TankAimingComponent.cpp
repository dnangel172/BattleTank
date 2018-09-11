// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h" //SuggestVelocity
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Projectile.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EFireState UTankAimingComponent::GetFireState() const { return FireState; }

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (ReloadTime > (FPlatformTime::Seconds() - LastTime))
	{
		FireState = EFireState::Reload;
	}
	else if (IsBarrelMove())
	{
		FireState = EFireState::Aim;
	}
	else
	{
		FireState = EFireState::Lock;
	}
}

void UTankAimingComponent::initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet)
{
	if (!ensure(BarrelToSet && TurrentToSet)) { return; }
	Barrel = BarrelToSet;
	Turrent = TurrentToSet;
}

bool UTankAimingComponent::IsBarrelMove()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForwardDirection = Barrel->GetForwardVector();
	return (!BarrelForwardDirection.Equals(AimDirection, 0.05f)); //Equals = 沒有在移動(false)
}

// Called from PlayerController
void UTankAimingComponent::AimTo(FVector HitLocation)
{
	if (!ensure(Barrel && Turrent)) { return; }
	{
		FVector LaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
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
		
		if (bHaveAimSolution)
		{
			AimDirection = LaunchVelocity.GetSafeNormal(); //從大砲位置到HitLocation的LookDirection
			MoveBarrelAndTurrent();
		}
	}
}

void UTankAimingComponent::MoveBarrelAndTurrent()
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //取得大砲的初始角度(Pitch, Yaw, Roll)
	auto AimRotator = AimDirection.Rotation(); //大砲看的方向的角度(Pitch, Yaw, Roll)
	auto DeltaRotator = AimRotator - BarrelRotator; //大砲需要移動的角度 
	
	Barrel->Elevate(DeltaRotator.Pitch);

	UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaRotator.Yaw)
		if (FMath::Abs(DeltaRotator.Yaw) > 180)
		{
			Turrent->Rotate(-(DeltaRotator.Yaw));
		}
		else
		{
			Turrent->Rotate(DeltaRotator.Yaw);
		}

}

// Called from BP
void UTankAimingComponent::Fire()
{
	if (FireState != EFireState::Reload)
	{
		if (!ensure(Barrel && ProjectileBP)) { return; }
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


