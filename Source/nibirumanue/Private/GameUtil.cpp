// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtil.h"

FVector RandomCircleBase(float R0, float EndRadius, float HalfCentralAngle)
{
    float R = FMath::Sqrt(FMath::RandRange(R0, 1.0f)) * EndRadius;
    float Theta = FMath::RandRange(-HalfCentralAngle, HalfCentralAngle); //FIXME:   
    return FVector(R * FMath::Cos(Theta), R * FMath::Sin(Theta), 0.0f);
}

FVector UGameUtil::RandomCircle(float StartRadius, float EndRadius)
{
    float R0 = StartRadius / EndRadius;
    return RandomCircleBase(R0, EndRadius, PI);
}
