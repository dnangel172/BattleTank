// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrent.h"
#include "Engine/World.h"


void UTankTurrent::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * RotationDegreePerSecond * GetWorld()->GetDeltaSeconds();

	AddRelativeRotation(FRotator(0, RotationChange, 0));
}

