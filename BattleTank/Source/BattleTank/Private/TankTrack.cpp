// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); // �إ�Onhit Function
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SidewaysForce();
	ForwardForce();
	CurrentThrottle = 0;
}

void UTankTrack::SidewaysForce()
{
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // �ưʳt�� ���n.
	auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	auto CorrectAcceleration = -SlipSpeed / DeltaTime * GetRightVector(); // �ưʤϦV�[�t    ps. / DetalTime �h�T�ӹs �ϦV�t���ܤj (*1000)
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectForce = (RootComponent->GetMass() * CorrectAcceleration) / 2; // F = m * a, / 2 �]�������Track
	RootComponent->AddForce(CorrectForce);
}

void UTankTrack::ForwardForce()
{
	auto ForceApply = GetForwardVector() * CurrentThrottle * MaxDrivingForce; //�I�O��V x,y > 1
	auto ForceLocation = GetComponentLocation(); //Track Location �I�O�I
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApply, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle += FMath::Clamp<float>(Throttle, -1, 1);
}
