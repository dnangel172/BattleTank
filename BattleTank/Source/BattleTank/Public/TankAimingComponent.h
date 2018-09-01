// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//forward declartion 
class UTanksBarrel; 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:
	//called from Tank throgh BP
	void AimTo(FVector HitLocation, float LaunchSpeed); 

	//called from Tank
	void SetBarrelComponent(UTanksBarrel* BarrelToSet);

	void MoveBarrel(FVector AimDirectRion);

private:
	UTanksBarrel* Barrel = nullptr;
		
};
