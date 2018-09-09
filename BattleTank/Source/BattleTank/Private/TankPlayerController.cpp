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
	GetViewportSize(ViewportSizeX, ViewportSizeY); // out parameter 取得視窗大小
	auto CrossHairScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY); // 取得CrossHair Location

	return GetLookDirectionAndLineTrace(CrossHairScreenLocation, HitLocation);

}

//LookDirection = 從攝影機位置看CrossHair的方向
bool ATankPlayerController::GetLookDirectionAndLineTrace(FVector2D CrossHairScreenLocation, FVector& HitLocation) const
{
	FVector CamLookLocation;
	FVector LookDirection;
	DeprojectScreenPositionToWorld
	(
		CrossHairScreenLocation.X,
		CrossHairScreenLocation.Y,
		CamLookLocation, // 攝影機看CrossHair的位置 out parameter
		LookDirection // 攝影機看CrossHair的方向 out parameter
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




