// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerArms.h"
#include "PlayerBullet.generated.h"

/**
 * 
 */
UCLASS()
class APlayerBullet : public APlayerArms
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APlayerBullet();
    void Setup(const FVector& InDir);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
    FVector mDir{ 0.0f };
    float mSpeed = 150.0f;
    union Flag {
        struct {
            bool ToBeDestroyed : 1;
        };
        uint8_t All = 0;
    } mFlag;
};
