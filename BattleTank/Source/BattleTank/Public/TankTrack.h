// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup=(Custom))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Called from TankMovementComponent
	void SetThrottle(float Throttle);
	
private:
	UTankTrack();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void SidewaysForce();

	void ForwardForce();

	//mass * accelerate = 400000 * 100
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDrivingForce = 40000000;

	float CurrentThrottle = 0;

};
