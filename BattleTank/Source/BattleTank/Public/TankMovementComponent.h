// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup=(Custom))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	// Called from BP
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initilize(UTankTrack* Track_LToSet, UTankTrack* Track_RToSet);

	// Called from BP
	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Axis);

	// Called from BP
	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveRight(float Axis);

private:
	UTankTrack* Track_L;
	UTankTrack* Track_R;

	// Called from the pathfinding logic by th AIController no need to public
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
