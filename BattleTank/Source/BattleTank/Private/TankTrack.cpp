// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // 滑動速度 內積.
	auto CorrectAcceleration = -SlipSpeed / DeltaTime * GetRightVector(); // 滑動反向加速    ps. / DetalTime 多三個零 反向速度變大 (*1000)
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectForce = (RootComponent->GetMass() * CorrectAcceleration) / 2; // F = m * a, / 2 因為有兩個Track
	RootComponent->AddForce(CorrectForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApply = GetForwardVector() * Throttle * MaxDrivingForce; //施力方向 x,y > 1
	auto ForceLocation = GetComponentLocation(); //Track Location 施力點
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApply, ForceLocation);
}


