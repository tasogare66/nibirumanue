// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

AEnemy::AEnemy()
{
    Tags.AddUnique(TEXT("Enemy"));
}

AEneSnake::AEneSnake()
{
}

void AEneSnake::Tick(float Deltatime)
{
}

void AEneSnake::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (UWorld* World = GetWorld())
    {
        World->DestroyActor(this);
    }
}
