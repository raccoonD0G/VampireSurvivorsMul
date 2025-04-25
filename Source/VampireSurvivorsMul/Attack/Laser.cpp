// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack/Laser.h"

ALaser::ALaser()
{
    PrimaryActorTick.bCanEverTick = false;

    SetLifeSpan(0.5f);
}
