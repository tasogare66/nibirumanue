// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPlayerController.h"

#include "GameFramework/InputSettings.h"

ATopDownPlayerController::ATopDownPlayerController()
{
}

void ATopDownPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    //キーボード
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveX", EKeys::A, -1.0f));
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveX", EKeys::D, 1.0f));
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveY", EKeys::W, -1.0f));
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveY", EKeys::S, 1.0f));
    //Gamepad
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveX", EKeys::Gamepad_LeftX, 1.0f));
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveY", EKeys::Gamepad_LeftY, -1.0f));
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("ShootX", EKeys::Gamepad_RightX, 1.0f));
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("ShootY", EKeys::Gamepad_RightY, -1.0f));

    InputComponent->BindAxis("MoveX", this, &ATopDownPlayerController::MoveXInput);
    InputComponent->BindAxis("MoveY", this, &ATopDownPlayerController::MoveYInput);
    InputComponent->BindAxis("ShootX", this, &ATopDownPlayerController::ShootXInput);
    InputComponent->BindAxis("ShootY", this, &ATopDownPlayerController::ShootYInput);
}

void ATopDownPlayerController::MoveXInput(const float Value)
{
    MoveVec.X = Value;
}

void ATopDownPlayerController::MoveYInput(const float Value)
{
    MoveVec.Y = Value;
}

void ATopDownPlayerController::ShootXInput(const float Value)
{
    ShootVec.X = Value;
}

void ATopDownPlayerController::ShootYInput(float Value)
{
    ShootVec.Y = Value;
}

void ATopDownPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto LambdaProcessAnalog = [](FVector2D& Vec) {
        Vec.X = FMath::Clamp(Vec.X, -1.0f, 1.0f);
        Vec.Y = FMath::Clamp(Vec.Y, -1.0f, 1.0f);
        const float len = Vec.Size();
        constexpr float AnalogThreshold = 0.5f;
        if (len > 1.0f) {
            Vec /= len; //1より大きい場合,normalizeしておく
        }
        else if (len < AnalogThreshold)
        {
            Vec = FVector2D::ZeroVector;
        }
    };
    LambdaProcessAnalog(MoveVec);
    LambdaProcessAnalog(ShootVec);
}
