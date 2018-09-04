// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Actor.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApply = GetForwardVector() * Throttle * MaxDrivingForce; //施力方向 x,y > 1
	auto ForceLocation = GetComponentLocation(); //Track Location 施力點
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApply, ForceLocation);
}


