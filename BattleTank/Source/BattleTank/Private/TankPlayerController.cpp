// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetTankActor() const
{
	return Cast<ATank>(GetPawn());
}


