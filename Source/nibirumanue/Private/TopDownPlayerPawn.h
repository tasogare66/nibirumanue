// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownPlayerPawn.generated.h"

UCLASS()
class NIBIRUMANUE_API ATopDownPlayerPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ATopDownPlayerPawn();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    void UpdateStatus(float DeltaTime);

    UFUNCTION()
    void Shoot(const FVector2D& InDir);

    float mShootRepeat = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Player")
    float MoveSpeed = 60.0f;
};
