// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initilize(UTankTrack* Track_LToSet, UTankTrack* Track_RToSet)
{
	if (!Track_LToSet || !Track_RToSet) { return; }
	Track_L = Track_LToSet;
	Track_R = Track_RToSet;
}



void UTankMovementComponent::MoveForward(float Axis)
{
	Track_L->SetThrottle(Axis);
	Track_R->SetThrottle(Axis);
}





