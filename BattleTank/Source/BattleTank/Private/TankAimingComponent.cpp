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
	return (!BarrelForwardDirection.Equals(AimDirection, 0.05f)); //Equals = �S���b����(false)
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
			StartLocation, //�j���f
			HitLocation, //CrossHair���۪���m
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
		
		if (bHaveAimSolution)
		{
			AimDirection = LaunchVelocity.GetSafeNormal(); //�q�j����m��HitLocation��LookDirection
			MoveBarrelAndTurrent();
		}
	}
}

void UTankAimingComponent::MoveBarrelAndTurrent()
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //���o�j������l����(Pitch, Yaw, Roll)
	auto AimRotator = AimDirection.Rotation(); //�j���ݪ���V������(Pitch, Yaw, Roll)
	auto DeltaRotator = AimRotator - BarrelRotator; //�j���ݭn���ʪ����� 
	
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
				ProjectileBP, //Spawn��Actor, �bBP��ܤF
				Barrel->GetSocketLocation(FName("Projectile")), //���u���X�ͦ�m
				Barrel->GetSocketRotation(FName("Projectil")) //���u����V
			);
		Projectile->Launch(LaunchSpeed);
		LastTime = FPlatformTime::Seconds();
	}
}


