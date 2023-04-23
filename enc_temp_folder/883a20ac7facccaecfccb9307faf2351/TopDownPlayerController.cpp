// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPlayerController.h"

#include "GameFramework/InputSettings.h"

ATopDownPlayerController::ATopDownPlayerController()
{
}

void ATopDownPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveX", EKeys::A, 1.0f));
    InputComponent->BindAxis("MoveX", this, &ATopDownPlayerController::MoveXInput);
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveX", EKeys::D, -1.0f));
    InputComponent->BindAxis("MoveX", this, &ATopDownPlayerController::MoveXInput);
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveY", EKeys::W, 1.0f));
    InputComponent->BindAxis("MoveY", this, &ATopDownPlayerController::MoveYInput);
    GetMutableDefault<UInputSettings>()->AddAxisMapping(FInputAxisKeyMapping("MoveY", EKeys::S, 1.0f));
    InputComponent->BindAxis("MoveY", this, &ATopDownPlayerController::MoveYInput);
}

void ATopDownPlayerController::MoveXInput(const float Value)
{
    MoveVec.X = Value;
}

void ATopDownPlayerController::MoveYInput(const float Value)
{
    MoveVec.Y = Value;
}

void ATopDownPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    MoveVec.X = FMath::Clamp(MoveVec.X, -1.0f, 1.0f);
    MoveVec.Y = FMath::Clamp(MoveVec.Y, -1.0f, 1.0f);
    const float len = MoveVec.Size();
    if (len < 0.01f) {
        MoveVec = FVector2D::ZeroVector;
    }
}
