// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack/Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = false;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

    // 기본 세팅
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    ProjectileMovement->ProjectileGravityScale = 0.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    InitialLifeSpan = 2.5f;
}

void ABullet::BeginPlay()
{
    Super::BeginPlay();

    FVector ForwardDir = GetActorForwardVector();
    ProjectileMovement->Velocity = ForwardDir * ProjectileMovement->InitialSpeed;
}
