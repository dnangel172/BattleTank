// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h" //X-Ray
#include "Engine/World.h" //LineTrace
#include "Tank.h" //Tank Actor


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPossessPawn())
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possess : %s"), *GetPossessPawn()->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTo();
}

ATank* ATankPlayerController::GetPossessPawn() const { return Cast<ATank>(GetPawn()); }

void ATankPlayerController::AimTo()
{
	if (!GetPossessPawn()) { return; } //ptr protect

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetPossessPawn()->AimTo(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); //out parameter 取得視窗大小
	auto CrossHairScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY); //取得CrossHair Location

	FVector LookDirection;
	if (GetLookDirection(CrossHairScreenLocation, LookDirection)) //out parameter
	{
		GetLookHitLocation(LookDirection, HitLocation); //out parameter
		return true;
	}
	return false;
}

//從攝影機位置看CrossHair的LookDirection
bool ATankPlayerController::GetLookDirection(FVector2D CrossHairScreenLocation, FVector& LookDirection) const
{
	FVector CamLookLocation; //To be discard
	return DeprojectScreenPositionToWorld
			(
				CrossHairScreenLocation.X,
				CrossHairScreenLocation.Y,
				CamLookLocation, //攝影機看CrossHair的位置 out parameter
				LookDirection //攝影機看CrossHair的方向 out parameter
			);
}


bool ATankPlayerController::GetLookHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) 
	{
		HitLocation = HitResult.Location; //out parameter
		return true;
	}
	HitLocation = FVector(0.0f);
	return false;
}



