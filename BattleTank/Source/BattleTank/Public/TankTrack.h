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
	// Called from TankMovementComponent and BP
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
private:
	//mass * accelerate
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDrivingForce = 400000; 
};
