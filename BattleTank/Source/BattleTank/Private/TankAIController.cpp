// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is aiming : %s"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find PlayerTank!"));
	}
}

ATank* ATankAIController::GetPossessPawn() const { return Cast<ATank>(GetPawn()); }

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; } //protect ptr
	return Cast<ATank>(PlayerTank);
}




