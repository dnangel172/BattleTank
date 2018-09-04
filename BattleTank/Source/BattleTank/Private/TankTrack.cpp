// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Actor.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApply = GetForwardVector() * Throttle * MaxDrivingForce; //�I�O��V x,y > 1
	auto ForceLocation = GetComponentLocation(); //Track Location �I�O�I
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApply, ForceLocation);
}


