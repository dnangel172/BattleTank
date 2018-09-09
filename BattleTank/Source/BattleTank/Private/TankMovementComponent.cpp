// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initilize(UTankTrack* Track_LToSet, UTankTrack* Track_RToSet)
{
	Track_L = Track_LToSet;
	Track_R = Track_RToSet;
}

void UTankMovementComponent::MoveForward(float Axis)
{
	if (!ensure(Track_L && Track_R)) { return; }
	Track_L->SetThrottle(Axis);
	Track_R->SetThrottle(Axis);
}

void UTankMovementComponent::MoveRight(float Axis)
{
	if (!ensure(Track_L && Track_R)) { return; }
	Track_L->SetThrottle(Axis);
	Track_R->SetThrottle(-Axis);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//¤£¥ÎSuper::
	auto TankLookDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto IntendDirection = MoveVelocity.GetSafeNormal();

	auto Dot = FVector::DotProduct(TankLookDirection, IntendDirection); //¤º¿n
	MoveForward(Dot);
	auto Cross = FVector::CrossProduct(TankLookDirection, IntendDirection).Z; //¤e¿n
	MoveRight(Cross);
}






