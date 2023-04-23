// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATopDownPlayerController : public APlayerController
{
    GENERATED_BODY()
    
public:
    ATopDownPlayerController();

    virtual void SetupInputComponent() override;
    virtual void Tick(float DeltaTime) override;

    FVector2D GetMoveVec() const { return MoveVec; }

private:
    void MoveXInput(float Value);
    void MoveYInput(float Value);
    
    UPROPERTY()
    FVector2D MoveVec = FVector2D(0.0f);
};
