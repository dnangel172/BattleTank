// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is aiming : %s"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find PlayerTank!"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetPlayerTank())
	{
		GetPossessPawn()->AimTo(GetPlayerTank()->GetActorLocation()); 
	}

}

ATank* ATankAIController::GetPossessPawn() const { return Cast<ATank>(GetPawn()); }

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; } //protect ptr

	return Cast<ATank>(PlayerTank);
}





