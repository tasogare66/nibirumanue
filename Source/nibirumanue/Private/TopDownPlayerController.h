// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

USTRUCT()
struct FInputData {
    GENERATED_BODY()

    FInputData() = default;
    FVector2D mMoveInput{ 0.0f }; //入力から渡される値,Clearで消さない
    FVector2D mShootInput{ 0.0f }; //入力から渡される値,Clearで消さない

    FVector2D mMove{ 0.0f }; //移動方向
    FVector2D mShootDir{ 0.0f }; //発射方向
    FVector2D mDashDir{ 0.0f }; //dash方向
    FVector2D mMeleeItemDir{ 0.0f }; //近接,item方向
    union Flag {
        struct {
            bool Joystick : 1;
            bool MoveOn : 1;
            bool ShootOn : 1;
            bool DashOn : 1;
            bool MeleeTrig : 1;
            bool ItemTrig : 1;
        };
        uint32_t All = 0;
    } Flag;
    void Clear() {
        mMove.Set(0.f, 0.f);
        mShootDir.Set(0.f, 0.f);
        mDashDir.Set(0.f, 0.f);
        mMeleeItemDir.Set(0.f, 0.f);
        Flag.All = 0;
    }
};

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

    const FInputData& GetInputData() const { return mInputData; }

private:
    void MoveXInput(float Value);
    void MoveYInput(float Value);
    void ShootXInput(float Value);
    void ShootYInput(float Value);

    UPROPERTY()
    FInputData mInputData;
};
