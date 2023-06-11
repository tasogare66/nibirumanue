// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameBaseActor.h"
#include "Enemy.generated.h"

class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class AEnemy : public AGameBaseActor
{
    GENERATED_BODY()

public:
    AEnemy();

    bool SubHealth(float v) {
        v = FMath::Max(v, 0.0f); //負の値は不可
        mHealth = FMath::Max(mHealth - v, 0.0f);
        mFlag.IsDead = (mHealth <= 0.0f);
        return mFlag.IsDead;
    }
    float GetHealth() const { return mHealth; }
    bool IsAlive() const { return !mFlag.IsDead; }

protected:
    virtual void Tick(float DeltaTime) override;

    // interface
    virtual void UpdateEne(float DeltaTime) {}

    void SpawnDefeatedEffect();

    float mHealth = 1.0f;
    union Flag {
        struct {
            bool IsDead : 1;
        };
        uint8_t All = 0;
    } mFlag;

    UPROPERTY(EditAnywhere, Category = "Effects")
    UNiagaraSystem* DefeatedEffect = nullptr;
};

UCLASS()
class AEneSnake : public AEnemy
{
    GENERATED_BODY()

public:
    AEneSnake() = default;

protected:
    virtual void UpdateEne(float DeltaTime) override;
};
