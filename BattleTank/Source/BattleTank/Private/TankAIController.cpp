// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControllerTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		ControllerTank->AimTo(PlayerTank->GetActorLocation());
		ControllerTank->Fire();
	}
}





