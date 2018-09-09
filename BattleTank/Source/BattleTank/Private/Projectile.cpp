// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//no need to protect ptr 
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called from AimingComp.
void AProjectile::Launch(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); //砲彈方向 = 大砲方向
	ProjectileMovementComponent->Activate();
}

