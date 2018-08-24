// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetPossessPawn())
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possess : %s"), *GetPossessPawn()->GetName());
	}
}

ATank* ATankPlayerController::GetPossessPawn() const
{
	return Cast<ATank>(GetPawn());
}


