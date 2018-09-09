// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // �ưʳt�� ���n.
	auto CorrectAcceleration = -SlipSpeed / DeltaTime * GetRightVector(); // �ưʤϦV�[�t    ps. / DetalTime �h�T�ӹs �ϦV�t���ܤj (*1000)
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectForce = (RootComponent->GetMass() * CorrectAcceleration) / 2; // F = m * a, / 2 �]�������Track
	RootComponent->AddForce(CorrectForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApply = GetForwardVector() * Throttle * MaxDrivingForce; //�I�O��V x,y > 1
	auto ForceLocation = GetComponentLocation(); //Track Location �I�O�I
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApply, ForceLocation);
}


