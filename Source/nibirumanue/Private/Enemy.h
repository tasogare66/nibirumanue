// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameBaseActor.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class AEnemy : public AGameBaseActor
{
    GENERATED_BODY()

public:
    AEnemy();
};

UCLASS()
class AEneSnake : public AEnemy
{
    GENERATED_BODY()

public:
    AEneSnake();

protected:
    virtual void Tick(float Deltatime) override;

    UFUNCTION()
    void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
