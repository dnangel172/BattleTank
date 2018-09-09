// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h" //LineTrace
#include "TankAimingComponent.h"



void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTo();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimComp)) { return; }
	SetAimCompRef(AimComp);
}

void ATankPlayerController::AimTo()
{
	auto AimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimComp)) { return; }
	
	FVector HitLocation; 
	if (GetSightRayHitLocation(HitLocation)) // out parameter
	{
		AimComp->AimTo(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); // out parameter ���o�����j�p
	auto CrossHairScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY); // ���oCrossHair Location

	return GetLookDirectionAndLineTrace(CrossHairScreenLocation, HitLocation);

}

//LookDirection = �q��v����m��CrossHair����V
bool ATankPlayerController::GetLookDirectionAndLineTrace(FVector2D CrossHairScreenLocation, FVector& HitLocation) const
{
	FVector CamLookLocation;
	FVector LookDirection;
	DeprojectScreenPositionToWorld
	(
		CrossHairScreenLocation.X,
		CrossHairScreenLocation.Y,
		CamLookLocation, // ��v����CrossHair����m out parameter
		LookDirection // ��v����CrossHair����V out parameter
	);

	FHitResult HitResult;
	FVector EndLocation = CamLookLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, CamLookLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location; //out parameter
		return true;
	}
	return false;
}




