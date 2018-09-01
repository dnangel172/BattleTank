// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * ElevateDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinDegrees, MaxDegrees) ;

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}

