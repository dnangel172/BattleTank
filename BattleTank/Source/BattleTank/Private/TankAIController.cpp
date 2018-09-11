// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius); // Call Pawn->NavMovementComponent µM«ácall requestdirectmove
		AimComp->AimTo(PlayerTank->GetActorLocation());

		if (AimComp->GetFireState() == EFireState::Lock)
		{
			AimComp->Fire();
		}
		
	}
}





