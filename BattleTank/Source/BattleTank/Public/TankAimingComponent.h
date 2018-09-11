// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFireState : uint8
{
	Reload,
	Aim,
	Lock
};

class UTankBarrel; 
class UTankTurrent;
class AProjectile;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);

	void AimTo(FVector HitLocation); 

	UFUNCTION(BlueprintCallable, Category= "Fire")
	void Fire();

	EFireState GetFireState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFireState FireState = EFireState::Reload;

private:
	void MoveBarrelAndTurrent();

	bool IsBarrelMove();

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float ReloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	TSubclassOf<AProjectile> ProjectileBP;

	float LastTime = FPlatformTime::Seconds();

	FVector AimDirection;

	UTankBarrel* Barrel = nullptr;
	UTankTurrent* Turrent = nullptr;


};
