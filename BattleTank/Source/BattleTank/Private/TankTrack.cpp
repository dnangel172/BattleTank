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
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); // 建立Onhit Function
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SidewaysForce();
	ForwardForce();
	CurrentThrottle = 0;
}

void UTankTrack::SidewaysForce()
{
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // 滑動速度 內積.
	auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	auto CorrectAcceleration = -SlipSpeed / DeltaTime * GetRightVector(); // 滑動反向加速    ps. / DetalTime 多三個零 反向速度變大 (*1000)
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectForce = (RootComponent->GetMass() * CorrectAcceleration) / 2; // F = m * a, / 2 因為有兩個Track
	RootComponent->AddForce(CorrectForce);
}

void UTankTrack::ForwardForce()
{
	auto ForceApply = GetForwardVector() * CurrentThrottle * MaxDrivingForce; //施力方向 x,y > 1
	auto ForceLocation = GetComponentLocation(); //Track Location 施力點
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApply, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle += FMath::Clamp<float>(Throttle, -1, 1);
}
