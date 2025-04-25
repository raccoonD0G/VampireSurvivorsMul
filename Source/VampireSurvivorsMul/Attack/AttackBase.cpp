// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack/AttackBase.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Collision/Collision.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAttackBase::AAttackBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    bReplicates = true;
}



// Called when the game starts or when spawned
void AAttackBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAttackBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

// Called every frame
void AAttackBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AAttackBase::GetDamage() const
{
    return 50.0f;
}

void AAttackBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (HasAuthority())
    {
        if (!OtherActor || OtherActor == GetOwner()) return;

        float DamageAmount = GetDamage();
        TSubclassOf<UDamageType> DamageTypeClass = UDamageType::StaticClass(); // 기본 데미지 타입

        UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, GetInstigatorController(), this, DamageTypeClass);
    }
    
}

