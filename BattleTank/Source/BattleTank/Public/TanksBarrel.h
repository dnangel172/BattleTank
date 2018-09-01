// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TanksBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Hidecategories = ("Collision"))
class BATTLETANK_API UTanksBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	//Called from TankAimingComponent
	void Elevate(float RelativeSpeed);
	

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinDegrees = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float ElevateDegreePerSecond = 10;

};
